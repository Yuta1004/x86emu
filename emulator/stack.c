#include <stdint.h>
#include "emulator.h"
#include "memory.h"
#include "stack.h"
#include "register.h"

void push32(Emulator *emu, uint32_t val)
{
    uint32_t addr = get_reg32(emu, ESP) - 4;
    set_reg32(emu, ESP, addr);
    write_mem32(emu, addr, val);
}

uint32_t pop32(Emulator *emu)
{
    uint32_t addr = get_reg32(emu, ESP);
    uint32_t val = read_mem32(emu, addr);
    set_reg32(emu, ESP, addr+4);
    return val;
}
