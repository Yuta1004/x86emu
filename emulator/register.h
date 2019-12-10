#ifndef REGISTERH
#define REGISTERH

/* ヘッダファイル */
#include <stdlib.h>
#include "emulator.h"

/* 定数 */
#define CARRY_FLAG          (1 << 0)
#define ZERO_FLAG           (1 << 6)
#define SIGN_FLAG           (1 << 7)
#define OVERFLOW_FLAG       (1 << 11)
#define get_flag(emu, POS)  ((((emu)->eflags)&(POS))>0)

/* 関数 */
uint32_t get_reg32(Emulator *emu, int reg_num);
void set_reg32(Emulator *emu, int reg_num, uint32_t val);
void update_eflags_sub(Emulator *emu, uint32_t val1, uint32_t val2);

#endif
