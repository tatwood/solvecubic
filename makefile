EXE=bin/testcubic
OBJS=obj/test.o obj/cubic.o
INCLUDES=
LIBS=-lm
CC=gcc
CCFLAGS=-Wall -O0 -ggdb2 -fno-exceptions -DDEBUG $(INCLUDES)
LD=gcc
LDFLAGS=$(LIBS)

vpath %.c src

$(EXE): obj bin $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

obj:
	mkdir obj

bin:
	mkdir bin

obj/%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

all: $(EXE)

clean:
	rm -rf $(EXE) obj
