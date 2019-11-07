#ifndef EMULATORH
#define EMULATORH

/* ヘッダファイル */
#include <stdlib.h>
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

/* 関数 */
// emulator.c
Emulator *create_emu(size_t mem_size, uint32_t eip, uint32_t esp);
void destroy_emu(Emulator *emu);

// memory.c
uint32_t get_code8(Emulator *emu, int idx);
int32_t get_sign_code8(Emulator *emu, int idx);
uint32_t get_code32(Emulator *emu, int idx);

#endif
