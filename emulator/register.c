#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "emulator.h"


/* レジスタ取得(32bit) */
uint32_t get_reg32(Emulator *emu, int reg_num)
{
    if(reg_num >= REGISTERS_COUNT) {
        printf("Failed to access to reg! => %d", reg_num);
        exit(1);
    }
    return emu->registers[reg_num];
}

/* レジスタ書き込み(32bit) */
void set_reg32(Emulator *emu, int reg_num, uint32_t val)
{
    if(reg_num >= REGISTERS_COUNT) {
        printf("Failed to access to reg! => %d", reg_num);
        exit(1);
    }
    emu->registers[reg_num] = val;
}
