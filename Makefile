CC = gcc
GCC = gcc
SRCS = $(wildcard *.c emulator/*.c)
OBJS = $(SRCS:.c=.o)
ARGS =

.PHONY: all clean

all:
	make build
	make run


build: $(OBJS)
	$(GCC) -o x86emu $(OBJS) $(LDFLAGS)


run:
	./x86emu $(ARGS)


clean:
	rm -rf *.o emulator/*.o
