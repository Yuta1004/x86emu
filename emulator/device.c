#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "device.h"

uint8_t io_in8(Emulator *emu, uint16_t port_addr)
{
    uint8_t inp;

    switch(port_addr) {
        case 0x03f8:
            inp = (uint8_t)getchar();
            while(getchar() != 10);
            return inp;

        default:
            return 0;
    }
}

void io_out8(Emulator *emu, uint16_t port_addr, uint8_t val)
{
    switch(port_addr) {
        case 0x03f8:
            putchar((char)val);
            return;

        default:
            return;
    }
}
