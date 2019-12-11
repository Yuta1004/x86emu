#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "emulator.h"
#include "memory.h"
#include "instruction.h"
#include "modrm.h"
#include "stack.h"
#include "register.h"

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

void mov_rm32_imm32(Emulator *emu, ModRM *modrm)
{
    uint32_t imm32 = get_code32(emu, 0);
    set_rm32(emu, modrm, imm32);
    emu->eip += 4;
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

void add_rm32_imm8(Emulator *emu, ModRM *modrm)
{
    uint32_t rm32 = get_rm32(emu, modrm);
    int8_t imm8 = get_sign_code8(emu, 0);
    set_rm32(emu, modrm, rm32+imm8);
    emu->eip += 1;
}

/* sub */
void sub_rm32_imm8(Emulator *emu, ModRM *modrm)
{
    uint32_t r32 = get_rm32(emu, modrm);
    uint32_t imm8 = (int32_t)get_sign_code8(emu, 0);
    set_rm32(emu, modrm, (uint64_t)r32-(uint64_t)imm8);
    update_eflags_sub(emu, r32, imm8);
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
    update_eflags_sub(emu, rm32, r32);
}

/* cmp */
void cmp_r32_rm32(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t r32 = get_r32(emu, &modrm);
    uint32_t rm32 = get_rm32(emu, &modrm);
    update_eflags_sub(emu, r32, rm32);
}

void cmp_rm32_imm8(Emulator *emu, ModRM *modrm)
{
    uint32_t rm32 = get_rm32(emu, modrm);
    uint32_t imm8 = (int32_t)get_sign_code8(emu, 0);    // 符号付き->符号なし(後で64bitに拡張するので問題ない)
    update_eflags_sub(emu, rm32, imm8);
    emu->eip += 1;
}

/* inc */
void inc_r32(Emulator *emu)
{
    uint8_t reg = get_code8(emu, 0) - 0x40;
    emu->registers[reg] += 1;
    emu->eip += 1;
}

void inc_rm32(Emulator *emu, ModRM *modrm)
{
    uint32_t rm32 = get_rm32(emu, modrm);
    set_rm32(emu, modrm, rm32+1);
}

/* dec */
void dec_r32(Emulator *emu)
{
    uint8_t reg = get_code8(emu, 0) - 0x48;
    emu->registers[reg] -= 1;
    emu->eip += 1;
}

void dec_rm32(Emulator *emu, ModRM *modrm)
{
    uint32_t val = get_rm32(emu, modrm);
    set_rm32(emu, modrm, val-1);
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

/* jcc */
define_jcc_func(c, CARRY_FLAG);
define_jcc_func(z, ZERO_FLAG);
define_jcc_func(s, SIGN_FLAG);
define_jcc_func(o, OVERFLOW_FLAG);

void jcc_jl(Emulator *emu)
{
    if(get_flag(emu, SIGN_FLAG) != get_flag(emu, OVERFLOW_FLAG))
        emu->eip += (int32_t)get_sign_code8(emu, 1);
    emu->eip += 2;
}

void jcc_jle(Emulator *emu)
{
    if(get_flag(emu, ZERO_FLAG) || get_flag(emu, SIGN_FLAG) != get_flag(emu, OVERFLOW_FLAG))
        emu->eip += (int32_t)get_sign_code8(emu, 1);
    emu->eip += 2;
}

void jcc_jnl(Emulator *emu)
{
    if(get_flag(emu, SIGN_FLAG) == get_flag(emu, OVERFLOW_FLAG))
        emu->eip += (int32_t)get_sign_code8(emu, 1);
    emu->eip += 2;
}

void jcc_jnle(Emulator *emu)
{
    if(get_flag(emu, ZERO_FLAG) && get_flag(emu, SIGN_FLAG) == get_flag(emu, OVERFLOW_FLAG))
        emu->eip += (int32_t)get_sign_code8(emu, 1);
    emu->eip += 2;
}

/* push */
void push_rm32(Emulator *emu, ModRM *modrm)
{
    uint32_t val = get_rm32(emu, modrm);
    push32(emu, val);
}

void push_r32(Emulator *emu)
{
    uint8_t reg = get_code8(emu, 0) - 0x50;
    push32(emu, get_reg32(emu, reg));
    emu->eip += 1;
}

void push_imm8(Emulator *emu)
{
    uint8_t val = get_code8(emu, 1);
    push32(emu, val);
    emu->eip += 2;
}

/* pop */
void pop_r32(Emulator *emu)
{
    uint8_t reg = get_code8(emu, 0) - 0x58;
    uint32_t val = pop32(emu);
    set_reg32(emu, reg, val);
    emu->eip += 1;
}

/* call */
void call_rel32(Emulator *emu)
{
    int32_t diff = get_sign_code32(emu, 1);
    emu->eip += 5;
    push32(emu, emu->eip);
    emu->eip += diff;
}

/* ret */
void ret(Emulator *emu)
{
    uint32_t addr = pop32(emu);
    emu->eip = addr;
}

/* leave */
void leave(Emulator *emu)
{
    set_reg32(emu, ESP, get_reg32(emu, EBP));
    set_reg32(emu, EBP, pop32(emu));
    emu->eip += 1;
}


/* code func */
void code_83(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch(modrm.opecode) {
    case 0:
        add_rm32_imm8(emu, &modrm);
        break;

    case 5:
        sub_rm32_imm8(emu, &modrm);
        break;

    case 7:
        cmp_rm32_imm8(emu, &modrm);
        break;

    default:
        printf("Not implemented : 83 /%d\n", modrm.opecode);
        break;
    }
}

void code_c7(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch(modrm.opecode){
    case 0:
        mov_rm32_imm32(emu, &modrm);
        break;

    default:
        printf("Not implemented : c7 /%d\n", modrm.opecode);
        break;
    }
}

void code_ff(Emulator *emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);

    switch(modrm.opecode){
    case 0:
        inc_rm32(emu, &modrm);
        break;

    case 1:
        dec_rm32(emu, &modrm);
        break;

    case 6:
        push_rm32(emu, &modrm);
        break;

    default:
        printf("Not implemented : ff /\%d\n", modrm.opecode);
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
    instructions[0xC7] = code_c7;

    // add
    instructions[0x01] = add_rm32_r32;  // add_rm16_r16
    instructions[0x03] = add_r32_rm32;  // add_r16_rm16

    // sub
    instructions[0x83] = code_83;       // sub_rm32_imm8, sub_rm16_imm8
    instructions[0x29] = sub_rm32_r32;  // sub_rm32_r32

    // cmp
    instructions[0x3B] = cmp_r32_rm32;

    // inc
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0x40+idx] = inc_r32;
    instructions[0xff] = code_ff;

    // dec
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0x48+idx] = dec_r32;

    // jmp
    instructions[0xEB] = short_jmp;
    instructions[0xE9] = near_jmp;

    // jcc
    instructions[0x70] = jcc_jo;
    instructions[0x71] = jcc_jno;
    instructions[0x72] = jcc_jc;
    instructions[0x73] = jcc_jnc;
    instructions[0x74] = jcc_jz;
    instructions[0x75] = jcc_jnz;
    instructions[0x78] = jcc_js;
    instructions[0x79] = jcc_jns;
    instructions[0x7C] = jcc_jl;
    instructions[0x7D] = jcc_jnl;
    instructions[0x7E] = jcc_jle;
    instructions[0x7F] = jcc_jnle;

    // push
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0x50+idx] = push_r32;
    instructions[0x6A] = push_imm8;

    // pop
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0x58+idx] = pop_r32;

    // call
    instructions[0xE8] = call_rel32;

    // ret
    instructions[0xC3] = ret;

    // leave
    instructions[0xC9] = leave;
}
