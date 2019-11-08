#ifndef INSTRUCTIONH
#define INSTRUCTIONH

/* ヘッダファイル */
#include "emulator.h"

/* 変数 */
typedef void instruction_func(Emulator*);
extern instruction_func* instructions[256];

/* 関数 */
void init_instruction_table();
void mov_r32_imm32(Emulator *emu);
void short_jmp(Emulator *emu);
void near_jmp(Emulator *emu);


#endif
