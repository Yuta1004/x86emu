#include <stdlib.h>
#include <stdio.h>
#include "emulator.h"

/* 命令読み取り(8bit */
uint32_t get_code8(Emulator *emu, int idx)
{
    return emu->memory[emu->eip+idx];
}

/* 命令読み取り(8bit, 符号付き)*/
int32_t get_sign_code8(Emulator *emu, int idx)
{
    return (int32_t)emu->memory[emu->eip+idx];
}

/* 命令読み取り(32bit) */
uint32_t get_code32(Emulator *emu, int idx)
{
    uint32_t val = 0;
    val |= emu->memory[emu->eip+idx+0] << 0;
    val |= emu->memory[emu->eip+idx+1] << 8;
    val |= emu->memory[emu->eip+idx+2] << 16;
    val |= emu->memory[emu->eip+idx+3] << 24;
    return val;
}
