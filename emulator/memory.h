#ifndef MEMORYH
#define MEMORYH

/* ヘッダファイル */
#include "emulator.h"

/* 関数 */
uint32_t read_mem8(Emulator *emu, int idx);
int32_t read_sign_mem8(Emulator *emu, int idx);
uint32_t read_mem32(Emulator *emu, int idx);
int32_t read_sign_mem32(Emulator *emu, int idx);


#endif
