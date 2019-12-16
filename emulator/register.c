#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "emulator.h"
#include "register.h"


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

/* レジスタ取得(8bit) */
uint8_t get_reg8(Emulator *emu, int reg_num)
{
    if(reg_num < 4) {
        return (uint8_t)(emu->registers[reg_num] & 0xff);
    } else {
        return (uint8_t)(emu->registers[reg_num-4] & 0xff00);
    }
}

/* レジスタ書き込み(8bit) */
void set_reg8(Emulator *emu, int reg_num, uint8_t val)
{
    if(reg_num < 4) {
        emu->registers[reg_num] &= ~(emu->registers[reg_num] & 0xff);
        emu->registers[reg_num] |= (uint8_t)val;
    } else {
        emu->registers[reg_num-4] &= ~(emu->registers[reg_num] & 0xff00);
        emu->registers[reg_num-4] |= (uint32_t)(val<<8);
    }
}

/* eflags更新(bit) */
void set_eflags_bit(Emulator *emu, uint8_t val, uint32_t target)
{
    if(val) {
        emu->eflags |= target;
    } else {
        emu->eflags &= ~target;     // 00010 -> 11101
    }
}

/* eflags更新 */
void update_eflags_sub(Emulator *emu, uint32_t val1, uint32_t val2)
{
    uint64_t sub_result = (uint64_t)val1 - (uint64_t)val2;

    uint8_t sign1 = (val1 >> 31);
    uint8_t sign2 = (val2 >> 31);
    uint8_t sign_res = (sub_result >> 31) & 1;  // 負の数になった時32bit以上は符号フラグで埋められている

    set_eflags_bit(emu, sub_result >> 32, CARRY_FLAG);
    set_eflags_bit(emu, sub_result == 0, ZERO_FLAG);
    set_eflags_bit(emu, sign_res, SIGN_FLAG);
    set_eflags_bit(emu, sign1 != sign2 && sign1 != sign_res, OVERFLOW_FLAG);
}

