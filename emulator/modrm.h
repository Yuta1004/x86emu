#ifndef MODRMH
#define MODRMH

/* ヘッダファイル */
#include <stdint.h>
#include "emulator.h"

/* 構造体(ModRM) */
typedef struct {

    uint8_t mod;
    union {
        uint8_t opecode;
        uint8_t reg_idx;
    };
    uint8_t rm;

    uint8_t sib;
    union {
        int8_t disp8;
        uint32_t disp32;
    };

} ModRM;

/* 関数 */
void parse_modrm(Emulator *emu, ModRM *modrm);
uint32_t get_r32(Emulator *emu, ModRM *modrm);
void set_r32(Emulator *emu, ModRM *modrm, uint32_t val);
uint32_t get_rm32(Emulator *emu, ModRM *modrm);
void set_rm32(Emulator *emu, ModRM *modrm, uint32_t val);

#endif
