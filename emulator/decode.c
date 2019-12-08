#include "decode.h"

char *opecode_dec_table[0xff];

void init_opecode_dec_table()
{

    /* mov */
    for(int idx = 0; idx < 8; ++ idx)
        opecode_dec_table[0xB8+idx] = "mov_r32_imm32";
    opecode_dec_table[0x89] = "mov_rm32_r32";
    opecode_dec_table[0x8B] = "mov_r32_rm32";
    opecode_dec_table[0xC7] = "code_c7";

    /* add */
    opecode_dec_table[0x01] = "add_rm32_r32";
    opecode_dec_table[0x03] = "add_r32_rm32";

    /* sub */
    opecode_dec_table[0x83] = "code_83";
    opecode_dec_table[0x29] = "sub_rm32_r32";

    /* inc */
    for(int idx = 0; idx < 8; ++ idx)
        opecode_dec_table[0x50+idx] = "inc_r32";
    opecode_dec_table[0xff] = "code_ff";

    /* dec */
    for(int idx = 0; idx < 8; ++ idx)
        opecode_dec_table[0x48+idx] = "rec_r32";

    /* jmp */
    opecode_dec_table[0xE8] = "short_jmp";
    opecode_dec_table[0xE9] = "near_jmp";

    /* push */
    for(int idx = 0; idx < 8; ++ idx)
        opecode_dec_table[0x50+idx] = "push_r32";

    /* pop */
    for(int idx = 0; idx < 8; ++ idx)
        opecode_dec_table[0x58+idx] = "pop_r32";

    /* call */
    opecode_dec_table[0xE8] = "call_rel32";

    /* ret */
    opecode_dec_table[0xC3] = "ret";

    /* leave */
    opecode_dec_table[0xC9] = "leave";

}
