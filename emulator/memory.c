#include <stdlib.h>
#include <stdio.h>
#include "emulator.h"
#include "memory.h"

/* メモリ読み取り(8bit */
uint32_t read_mem8(Emulator *emu, int idx)
{
    return emu->memory[emu->eip+idx];
}

/* メモリ読み取り(8bit, 符号付き)*/
int32_t read_sign_mem8(Emulator *emu, int idx)
{
    return (int32_t)emu->memory[emu->eip+idx];
}

/* メモリ読み取り(32bit) */
uint32_t read_mem32(Emulator *emu, int idx)
{
    uint32_t val = 0;
    val |= emu->memory[emu->eip+idx+0] << 0;
    val |= emu->memory[emu->eip+idx+1] << 8;
    val |= emu->memory[emu->eip+idx+2] << 16;
    val |= emu->memory[emu->eip+idx+3] << 24;
    return val;
}

/* メモリ読み取り(32bit, 符号つき) */
int32_t read_sign_mem32(Emulator *emu, int idx)
{
    return (int32_t)read_mem32(emu, idx);
}

