#ifndef MEMORYH
#define MEMORYH

/* ヘッダファイル */
#include "emulator.h"

/* 関数 */
uint32_t get_code8(Emulator *emu, int idx);
int32_t get_sign_code8(Emulator *emu, int idx);
uint32_t get_code32(Emulator *emu, int idx);
int32_t get_sign_code32(Emulator *emu, int idx);

uint32_t read_mem8(Emulator *emu, uint32_t addr);
int32_t read_sign_mem8(Emulator *emu, uint32_t addr);
uint32_t read_mem32(Emulator *emu, uint32_t addr);
int32_t read_sign_mem32(Emulator *emu, uint32_t addr);

void write_mem8(Emulator *emu, uint32_t addr, uint32_t val);
void write_mem32(Emulator *emu, uint32_t addr, uint32_t val);


#endif
