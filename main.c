#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "emulator/emulator.h"
#include "emulator/instruction.h"
#include "emulator/memory.h"
#include "emulator/decode.h"

#define MEMORY_SIZE 0xffff

int main(int argc, char *argv[])
{
    FILE *binary;
    Emulator *emu;
    init_instruction_table();
    init_opecode_dec_table();

    // 引数チェック
    if(argc != 2) {
        printf("Usage: %s x86_filename\n", argv[0]);
        return 1;
    }

    // エミュレータ作成
    emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);

    // x86プログラムファイル読み込み
    binary = fopen(argv[1], "rb");
    if(binary == NULL) {
        printf("x86 File not found! : %s\n", argv[1]);
        return 1;
    }

    // メモリにx86プログラムを配置する(8バイト単位)
    fread(emu->memory+0x7c00, 1, 0x200, binary);
    fclose(binary);

    // 命令実行
    while(emu->eip < MEMORY_SIZE) {
        uint8_t opecode = get_code8(emu, 0);
        if(instructions[opecode] == NULL){
            printf("Not impl => EIP: 0x%08x, Opecode: 0x%02x\n", emu->eip, opecode);
            puts("!!EMULATOR CRASH!!!");
            break;
        }

        char *dec_str = opecode_dec_table[opecode];
        printf("EIP: 0x%08x, OpeCode: 0x%02x, Decipher: %s\n", emu->eip, opecode, dec_str);

        instructions[opecode](emu);
        if(emu->eip == 0x00) {
            puts("!!End of program!!");
            break;
        }
    }

    puts("");
    display_reg_emu(emu);
    destroy_emu(emu);
    return 0;
}
