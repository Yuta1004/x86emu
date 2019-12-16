#ifndef DEVICE_H
#define DEVICE_H

/* ヘッダファイル */
#include <stdint.h>
#include "emulator.h"

/* 関数 */
uint8_t io_in8(Emulator *emu, uint16_t port_addr);
void io_out8(Emulator *emu, uint16_t port_addr, uint8_t val);

#endif
