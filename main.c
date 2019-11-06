#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "emulator/emulator.h"

#define MEMORY_SIZE 1000

int main(int argc, char *argv[])
{
    FILE *binary;
    Emulator *emu;

    // 引数チェック
    if(argc != 2) {
        printf("Usage: %s x86_filename\n", argv[0]);
        return 1;
    }

    // エミュレータ作成
    emu = create_emu(MEMORY_SIZE, 0x0000, 0x7c00);

    // x86プログラムファイル読み込み
    binary = fopen(argv[1], "rb");
    if(binary == NULL) {
        printf("x86 File not found! : %s\n", argv[1]);
        return 1;
    }

    // メモリにx86プログラムを配置する(8バイト単位)
    fread(emu->memory, 1, 0x200, binary);
    fclose(binary);

    destroy_emu(emu);
    return 0;
}
