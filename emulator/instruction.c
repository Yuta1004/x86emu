#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "emulator.h"

/* オペコードとそれを処理する関数の対応表 */
void init_instruction_table()
{
    memset(instructions, 0, sizeof(instructions));

    // mov
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0xB8+idx] = mov_r32_imm32;

    // short_jmp
    instructions[0xEB] = instructions;
}


/* mov(32bit) */
void mov_r32_imm32(Emulator *emu)
{
    uint8_t reg = get_code8(emu, 0) - 0xB8;
    uint32_t val = get_code32(emu, 1);
    emu->registers[reg] = val;
    return;
}

/* jmp(1byte) */
void short_jmp(Emulator *emu)
{
    int8_t adiff = get_sign_code8(emu, 1);
    emu->eip += 2;      // short_jmp命令のサイズ
    emu->eip += adiff;
    return;
}
