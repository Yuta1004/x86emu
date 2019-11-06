#ifndef EMULATORH
#define EMULATORH

/* ヘッダファイル */
#include <stdint.h>

/* 定数 */
#define REGISTERS_COUNT 8
#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7

/* 構造体 */
typedef struct {

    // 汎用レジスタ
    uint32_t registers[REGISTERS_COUNT];

    // EFLAGSレジスタ
    uint32_t eflags;

    // メモリ
    uint8_t *memory;

    // EIPレジスタ(プログラムカウンタ)
    uint32_t eip;

} Emulator;

#endif
