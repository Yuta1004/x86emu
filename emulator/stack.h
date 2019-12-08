#ifndef STACKH
#define STACKH

/* ヘッダファイル */
#include <stdint.h>
#include "emulator.h"

/* 関数 */
void push8(Emulator *emu, uint8_t val);
void push32(Emulator *emu, uint32_t val);
uint8_t pop8(Emulator *emu);
uint32_t pop32(Emulator *emu);

#endif
