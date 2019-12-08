# for build(emulator)
CC = gcc
GCC = gcc

# for build(i386program)
i386GCC = i386-elf-gcc
i386LD = i386-elf-ld
NASM = nasm
i386GCC_OPTS = -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector
i386LD_OPTS = --entry=start --oformat=binary -Ttext 0x7c00
NASM_OPTS = -f elf

# utils
OBJDUMP_OPTS = -M intel -d

# args
SRCS = $(wildcard *.c emulator/*.c)
OBJS = $(SRCS:.c=.o)
ARGS =

.PHONY: all clean

all:
	make build
	make run


build: $(OBJS)
	$(GCC) -o x86emu $(OBJS) $(LDFLAGS)


build-i386-program:
	$(NASM) $(NASM_OPTS) i386program/crt0.asm
	$(i386GCC) $(i386GCC_OPTS) -o i386program/main.o -c i386program/main.c
	$(i386LD) $(i386LD_OPTS) -o program i386program/crt0.o i386program/main.o
	hexdump program
	objdump $(OBJDUMP_OPTS) i386program/main.o


run-i386-program-on-emu: build program
	make run ARGS=program


run:
	./x86emu $(ARGS)


clean:
	rm -rf *.o emulator/*.o i386program/*.o
