#include <stdlib.h>
#include <stdio.h>
#include "emulator.h"
#include "memory.h"

/* 命令読み取り(8bit) */
uint8_t get_code8(Emulator *emu, int idx)
{
    return emu->memory[emu->eip+idx];
}

/* 命令読み取り(8bit, 符号付き)*/
int8_t get_sign_code8(Emulator *emu, int idx)
{
    return (int32_t)get_code8(emu, idx);
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

/* 命令読み取り(32bit, 符号つき) */
int32_t get_sign_code32(Emulator *emu, int idx)
{
    return (int32_t)get_code32(emu, idx);
}

/* メモリ読み取り(8bit) */
uint8_t read_mem8(Emulator *emu, uint32_t addr)
{
    return emu->memory[addr];
}

/* メモリ読み取り(8bit, 符号付き)*/
int8_t read_sign_mem8(Emulator *emu, uint32_t addr)
{
    return (int32_t)read_mem8(emu, addr);
}

/* メモリ読み取り(32bit) */
uint32_t read_mem32(Emulator *emu, uint32_t addr)
{
    uint32_t val = 0;
    val |= emu->memory[addr+0] << 0;
    val |= emu->memory[addr+1] << 8;
    val |= emu->memory[addr+2] << 16;
    val |= emu->memory[addr+3] << 24;
    return val;
}

/* メモリ読み取り(32bit, 符号つき) */
int32_t read_sign_mem32(Emulator *emu, uint32_t addr)
{
    return (int32_t)read_mem32(emu, addr);
}

/* メモリ書き込み(8bit) */
void write_mem8(Emulator *emu, uint32_t addr, uint32_t val)
{
    emu->memory[addr] = val & 0xFF;
}

/* メモリ書き込み(32bit) */
void write_mem32(Emulator *emu, uint32_t addr, uint32_t val)
{
    for(int idx = 0; idx < 4; ++ idx) {
        write_mem8(emu, addr+idx, val >> (idx*8));
    }
}
