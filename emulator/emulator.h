#ifndef EMULATORH
#define EMULATORH

/* ヘッダファイル */
#include <stdlib.h>
#include <stdint.h>

/* 定数 */
enum Register {
    EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTERS_COUNT,
    AL=EAX,  CL=ECX,  DL=EDX,  BL=EBX,
    AH=CL+4, CH=CL+4, DH=DL+4, BH=BL+4
};

/* 構造体(Emulator) */
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
Emulator *create_emu(size_t mem_size, uint32_t eip, uint32_t esp);
void destroy_emu(Emulator *emu);
void display_reg_emu(Emulator *emu);

/* 変数 */
typedef void instruction_func(Emulator*);
instruction_func* instructions[256];

#endif
