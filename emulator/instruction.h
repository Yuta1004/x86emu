#ifndef INSTRUCTIONH
#define INSTRUCTIONH

/* ヘッダファイル */
#include "emulator.h"

/* 変数 */
typedef void instruction_func(Emulator*);
extern instruction_func* instructions[256];

/* 関数 */
void init_instruction_table();

#endif
