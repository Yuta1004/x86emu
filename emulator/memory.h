#ifndef MEMORYH
#define MEMORYH

/* ヘッダファイル */
#include "emulator.h"

/* 関数 */
uint32_t get_code8(Emulator *emu, int idx);
int32_t get_sign_code8(Emulator *emu, int idx);
uint32_t get_code32(Emulator *emu, int idx);
int32_t get_sign_code32(Emulator *emu, int idx);


#endif
