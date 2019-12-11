#ifndef INSTRUCTIONH
#define INSTRUCTIONH

/* ヘッダファイル */
#include "emulator.h"

/* マクロ */
#define define_jmp_func(name, flag) \
    void j##name(Emulator *emu) \
    { \
        int8_t diff = get_flag(emu, flag) ? get_sign_code8(emu, 1) : 0;\
        emu->eip += (diff+2); \
    } \
    void jn##name(Emulator *emu) \
    { \
        int8_t diff = !get_flag(emu, flag) ? get_sign_code8(emu, 1) : 0;\
        emu->eip += (diff+2); \
    }

/* 変数 */
typedef void instruction_func(Emulator*);
extern instruction_func* instructions[256];

/* 関数 */
void init_instruction_table();

#endif
