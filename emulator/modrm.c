#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "emulator.h"
#include "memory.h"
#include "modrm.h"
#include "register.h"

/* Mod/RMの値を解析する */
void parse_modrm(Emulator *emu, ModRM *modrm)
{
    int aidx = 0;
    memset(modrm, 0, sizeof(ModRM));

    uint8_t code = read_mem8(emu, aidx);
    modrm->mod     = (code & 0b11000000) >> 6;
    modrm->opecode = (code & 0b00111000) >> 3;
    modrm->rm      = (code & 0b00000111) >> 0;
    emu->eip += 1;

    if(modrm->mod != 0b11 && modrm->rm == 0b100){
        modrm->sib = read_mem8(emu, (++aidx));
        emu->eip += 1;
    }

    if((modrm->mod == 0b00 && modrm->rm == 0b101) || modrm->mod == 0b01) {
        modrm->disp32 = read_mem32(emu, (++aidx));
        emu->eip += 4;
    } else if(modrm->mod == 0b10) {
        modrm->disp8 = read_sign_mem8(emu, (++aidx));
        emu->eip += 1;
    }
}

/* Mod/RMの値を元にメモリアドレスを計算する */
uint32_t calc_mem_addr(Emulator *emu, ModRM *modrm)
{

    switch(modrm->mod) {
    case 0b00:
        if(modrm->rm == 0b100) {
            puts("Not implemented => Mod: 00(0) , R/M: 100(4)");
            exit(1);
        } else if(modrm->rm == 0b101) {
            return modrm->disp32;
        } else {
            return get_reg32(emu, modrm->rm);
        }

    case 0b01:
        if(modrm->rm == 0b100) {
            puts("Not implemented => Mod: 01(1), R/M: 100(4)");
            exit(1);
        } else {
            return get_reg32(emu, modrm->rm) + modrm->disp8;
        }

    case 0b10:
        if(modrm->rm == 0b100) {
            puts("Not implemented => Mod: 10(2), R/M: 100(4)");
            exit(1);
        } else {
            return get_reg32(emu, modrm->rm) + modrm->disp32;
        }

    case 0b11:
    default:
        puts("Not implemented => Mod: 11(3)");
        exit(1);
    }
}

/* Mod/RMの値を元にレジスタ/メモリ読み込みを行う */
uint32_t get_rm32(Emulator *emu, ModRM *modrm)
{
    if(modrm->mod == 0b11) {
        return get_reg32(emu, modrm->rm);
    } else {
        return read_mem32(emu, calc_mem_addr(emu, modrm));
    }
}

/* Mod/RMの値を元にレジスタ/メモリ書き込みを行う */
void set_rm32(Emulator *emu, ModRM *modrm, uint32_t val)
{
    if(modrm->mod == 0b11) {
        set_reg32(emu, modrm->rm, val);
    } else {
        write_mem32(emu, calc_mem_addr(emu, modrm), val);
    }
}
