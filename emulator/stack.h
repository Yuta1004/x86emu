#ifndef STACKH
#define STACKH

/* ヘッダファイル */
#include <stdint.h>
#include "emulator.h"

/* 関数 */
void push32(Emulator *emu, uint32_t reg);
uint32_t pop32(Emulator *emu);

#endif
