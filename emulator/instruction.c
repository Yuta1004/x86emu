#include <stdlib.h>
#include <stdint.h>
#include "emulator.h"


/* mov(32bit) */
void mov_r32_imm32(Emulator *emu) {
    uint8_t reg = get_code8(emu, 0) - 0xB8;
    uint32_t val = get_code32(emu, 1);
    emu->registers[reg] = val;
    return;
}

/* jmp(1byte) */
void short_jmp(Emulator *emu) {
    int8_t adiff = get_sign_code8(emu, 1);
    emu->eip += adiff;
    return;
}
