#ifndef EMULATORH
#define EMULATORH

#include <stdint.h>

#define REGISTERS_COUNT 8

typedef struct {

    /* 汎用レジスタ */
    uint32_t registers[REGISTERS_COUNT];

    /* EFLAGSレジスタ */
    uint32_t eflags;

    /* メモリ */
    uint8_t *memory;

    /* EIPレジスタ(プログラムカウンタ) */
    uint32_t eip;

} Emulator;

#endif
