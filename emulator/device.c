#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "device.h"

uint8_t io_in8(uint16_t port_addr)
{
    switch(port_addr) {
        case 0x03f8:
            return (uint8_t)getchar();

        default:
            return 0;
    }
}

void io_out8(uint16_t port_addr, uint8_t val)
{
    switch(port_addr) {
        case 0x03f8:
            putchar((char)val);
            return;

        default:
            return;
    }
}
