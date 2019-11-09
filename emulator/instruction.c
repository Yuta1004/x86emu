#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "emulator.h"
#include "memory.h"
#include "instruction.h"

/* オペコードとそれを処理する関数の対応表 */
void init_instruction_table()
{
    memset(instructions, 0, sizeof(instructions));

    // mov
    for(int idx = 0; idx < 8; ++ idx)
        instructions[0xB8+idx] = mov_r32_imm32;

    // jmp
    instructions[0xEB] = short_jmp;
    instructions[0xE9] = near_jmp;
}


/* mov(32bit) */
void mov_r32_imm32(Emulator *emu)
{
    uint8_t reg = read_mem8(emu, 0) - 0xB8;
    uint32_t val = read_mem32(emu, 1);
    emu->registers[reg] = val;
    emu->eip += 5;
    return;
}

/* short jmp(8bit) */
void short_jmp(Emulator *emu)
{
    int8_t adiff = read_sign_mem8(emu, 1);
    emu->eip += 2;
    emu->eip += adiff;
    return;
}

/* near jmp(32bit) */
void near_jmp(Emulator *emu)
{
    int32_t adiff = read_sign_mem32(emu, 1);
    emu->eip += 5;
    emu->eip += adiff;
    return;
}
