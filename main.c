#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "emulator/emulator.h"
#include "emulator/instruction.h"
#include "emulator/memory.h"
#include "emulator/decode.h"

#define MEMORY_SIZE 0xffff

int remove_opt_at(int argc, char *argv[], int arg_idx)
{
    if(arg_idx < 0 || argc <= arg_idx)
        return argc;

    for(int idx = arg_idx; idx < argc-1; ++ idx) {
        argv[idx] = argv[idx+1];
    }
    argv[argc-1] = NULL;
    return argc-1;
}

int main(int argc, char *argv[])
{
    FILE *binary;
    Emulator *emu;
    bool varbose = false;
    init_instruction_table();
    init_opecode_dec_table();

    // 実行時オプションチェック
    for(int arg_idx = 0; arg_idx < argc; ++ arg_idx) {
        if(strncmp(argv[arg_idx], "--varbose", 2) == 0) {
            varbose = true;
            argc = remove_opt_at(argc, argv, arg_idx);
        }
    }

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
        if(varbose)
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
        if(varbose)
            printf("EIP: 0x%08x, OpeCode: 0x%02x, Inst: %s\n", emu->eip, opecode, dec_str);

        instructions[opecode](emu);
        if(emu->eip == 0x00) {
            if(varbose)
                puts("!!End of program!!");
            break;
        }
    }

    puts("");
    display_reg_emu(emu);
    destroy_emu(emu);
    return 0;
}
