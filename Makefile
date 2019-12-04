CC = gcc
GCC = gcc
NASM = nasm
HEXDUMP = hexdump
SRCS = $(wildcard *.c emulator/*.c)
OBJS = $(SRCS:.c=.o)
ARGS =

.PHONY: all clean

all:
	make build
	make run


build: $(OBJS)
	$(GCC) -o x86emu $(OBJS) $(LDFLAGS)


build-i386-program: program.asm
	$(NASM) program.asm
	$(HEXDUMP) program


run-i386-program-on-emu: build program
	make run ARGS=program


run:
	./x86emu $(ARGS)


clean:
	rm -rf *.o emulator/*.o
