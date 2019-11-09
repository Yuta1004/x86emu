#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "emulator.h"
#include "memory.h"
#include "modrm.h"

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
