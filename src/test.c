/**
 * @brief     unit test for cubic solver implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __GNUC__
#include <fenv.h>
#endif // __GNUC__

extern int solve_cubic(float a, float b, float c, float d, float* xout);

int main(int argc, char* argv[])
{
    int seed = time(NULL);
    clock_t t0;
    double dt;
    int i;

#ifdef __GNUC__
    feenableexcept(FE_DIVBYZERO|FE_UNDERFLOW|FE_OVERFLOW|FE_INVALID);
#endif // __GNUC__

    if(argc == 2)
    {
        sscanf(argv[1], "%x", &seed);
    }
    srand(seed);
    printf("seed: %x\n", seed);
    for(i = 0; i < 128*128; ++i)
    {
        // randomly generate parameters
        float a = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float b = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float c = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float d = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float px[3];
        int j;
        int n;
        const char* type = "";
        // solve the equation
        n = solve_cubic(a, b, c, d, px);
        if(fabs(a) > FLT_EPSILON && fabs(d) > FLT_EPSILON)
        {
            type = "cubic";
        }
        else if(fabs(b) > FLT_EPSILON)
        {
            type = "quadratic";
        }
        else
        {
            type = "linear";
        }
        printf("i=%i a=%f b=%f c=%f d=%f n=%i (%s)\n",i,a,b,c,d,n,type);
        for(j = 0; j < n; ++j)
        {
            // check the results
            float x = px[j];
            float zero = a*x*x*x + b*x*x + c*x + d;
            if(zero*zero <= 1e-5f)
            {
                printf("\tx%i=%f zero=%f\n",j,x,zero);        
            }
            else
            {
                printf("\tx%i=%f zero=%f (bad)\n",j,x,zero);
            }
        }
    }
    // run a bunch of tests without io to record timing
    t0 = clock();
    for(i = 0; i < 1024*1024; ++i)
    {
        // randomly generate parameters
        float a = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float b = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float c = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float d = (((float) rand())/RAND_MAX) * ((rand() % 8) - 4);
        float px[3];
        int n;
        // solve the equation
        n = solve_cubic(a, b, c, d, px);
    }
    dt = (clock() - t0)/((double) CLOCKS_PER_SEC);
    printf("time: %f\n", dt);
    return EXIT_SUCCESS;
}
