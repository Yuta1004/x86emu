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
    uint32_t rm32 = get_rm32(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    set_rm32(emu, &modrm, rm32+r32);
}

void add_r32_rm32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    set_r32(emu, &modrm, r32+rm32);
}

/* sub */
void sub_rm32_imm8(Emulator *emu, ModRM *modrm)
{
    uint32_t r32 = get_rm32(emu, modrm);
    int8_t imm8 = get_sign_code8(emu, 0);
    set_rm32(emu, modrm, r32-imm8);
    emu->eip += 1;
}

void sub_rm32_r32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    set_rm32(emu, &modrm, rm32-r32);
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

/* code func */
void code_83(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch(modrm.opecode) {
    case 5:
        sub_rm32_imm8(emu, &modrm);
        break;

    default:
        printf("Not implemented : 83 /%d\n", modrm.opecode);
        break;
    }
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

    // sub
    instructions[0x83] = code_83;       // sub_rm32_imm8, sub_rm16_imm8
    instructions[0x29] = sub_rm32_r32;  // sub_rm32_r32

    // jmp
    instructions[0xEB] = short_jmp;
    instructions[0xE9] = near_jmp;
}
