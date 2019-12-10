#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "emulator.h"
#include "register.h"

/* エミュレータ作成 */
Emulator *create_emu(size_t mem_size, uint32_t eip, uint32_t esp)
{
    // 初期化
    Emulator *emu = malloc(sizeof(Emulator));
    emu->memory = malloc(mem_size);

    // レジスタ初期化
    memset(emu->registers, 0, sizeof(emu->registers));
    emu->registers[ESP] = esp;
    emu->eip = eip;

    return emu;
}

/* エミュレータ削除 */
void destroy_emu(Emulator *emu)
{
    free(emu->memory);
    free(emu);
}

/* レジスタ表示 */
void display_reg_emu(Emulator *emu)
{
    static char* regs[]= {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};
    for(int idx = 0; idx < 8; ++ idx)
        printf("%s: 0x%08x\n", regs[idx], emu->registers[idx]);
    printf("EIP: 0x%08x\n", emu->eip);
    printf("EFLAGS:\n");
    printf("    - CF: %d\n", get_flag(emu, CARRY_FLAG));
    printf("    - ZF: %d\n", get_flag(emu, ZERO_FLAG));
    printf("    - SF: %d\n", get_flag(emu, SIGN_FLAG));
    printf("    - OF: %d\n", get_flag(emu, OVERFLOW_FLAG));
}
