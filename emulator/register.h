#ifndef REGISTERH
#define REGISTERH

/* ヘッダファイル */
#include <stdlib.h>
#include "emulator.h"

/* 関数 */
uint32_t get_reg32(Emulator *emu, int reg_num);
void set_reg32(Emulator *emu, int reg_num, uint32_t val);

#endif
