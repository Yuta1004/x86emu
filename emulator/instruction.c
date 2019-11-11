#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "emulator.h"
#include "memory.h"
#include "instruction.h"
#include "modrm.h"

/* mov */
void mov_r32_imm32(Emulator *emu)
{
    uint8_t reg = get_code8(emu, 0) - 0xB8;
    uint32_t val = get_code32(emu, 1);
    emu->registers[reg] = val;
    emu->eip += 5;
    return;
}

void mov_r32_rm32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t val = get_rm32(emu, &modrm);
    set_r32(emu, &modrm, val);
}

void mov_rm32_r32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t val = get_r32(emu, &modrm);
    set_rm32(emu, &modrm, val);
}

/* add */
void add_rm32_r32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t val_a_rm32 = get_rm32(emu, &modrm);
    uint32_t val_b_r32 = get_r32(emu, &modrm);
    set_rm32(emu, &modrm, val_a_rm32+val_b_r32);
}

void add_r32_rm32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t val_a_r32 = get_r32(emu, &modrm);
    uint32_t val_b_rm32 = get_rm32(emu, &modrm);
    set_r32(emu, &modrm, val_a_r32+val_b_rm32);
}


/* jmp */
void short_jmp(Emulator *emu)
{
    int8_t adiff = get_sign_code8(emu, 1);
    emu->eip += 2;
    emu->eip += adiff;
    return;
}

void near_jmp(Emulator *emu)
{
    int32_t adiff = get_sign_code32(emu, 1);
    emu->eip += 5;
    emu->eip += adiff;
    return;
}

/* オペコードとそれを処理する関数の対応表 */
void init_instruction_table()
{
    memset(instructions, 0, sizeof(instructions));

    // mov
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0xB8+idx] = mov_r32_imm32;
    instructions[0x89] = mov_rm32_r32;
    instructions[0x8B] = mov_r32_rm32;

    // add
    instructions[0x01] = add_rm32_r32;  // add_rm16_r16
    instructions[0x03] = add_r32_rm32;  // add_r16_rm16

    // jmp
    instructions[0xEB] = short_jmp;
    instructions[0xE9] = near_jmp;
}
