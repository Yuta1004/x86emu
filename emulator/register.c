#include <stdlib.h>
#include <stdint.h>
#include "emulator.h"


/* レジスタ取得(32bit) */
uint32_t get_reg32(Emulator *emu, int reg_num)
{
    if(reg_num >= REGISTERS_COUNT)
        return 0;
    return emu->registers[reg_num];
}

/* レジスタ書き込み(32bit) */
void set_reg32(Emulator *emu, int reg_num, uint32_t val)
{
    if(reg_num >= REGISTERS_COUNT)
        return;
    emu->registers[reg_num] = val;
}
