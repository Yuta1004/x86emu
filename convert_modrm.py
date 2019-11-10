#!/usr/bin/env python3

import sys

REGS = ["EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"]
regs = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]


def convert_modrm(modrm):
    if modrm >= (2<<8):
        print("ModR/M format error")
        return

    mod = (modrm & 0b11000000) >> 6
    reg = (modrm & 0b00111000) >> 3
    rm =  (modrm & 0b00000111) >> 0
    return (mod, reg, rm)


def format_mod_rm(mod, rm):
    if mod == 0b00:
        if rm == 0b100:
            return "[-][-]"
        elif rm == 0b101:
            return "disp32"
        else:
            return "["+regs[rm]+"]"

    if mod == 0b01:
        if rm == 0b100:
            return "[-][-]+disp8"
        else:
            return "["+regs[rm]+"]+disp8"

    if mod == 0b10:
        if rm == 0b100:
            return "[-][-]+disp32"
        else:
            return "["+regs[rm]+"]+disp32"

    return regs[rm]


def format_reg(reg):
    return REGS[reg]


def main():
    if len(sys.argv) <= 1:
        print("Usage: python3 convert_modrm.py ModR/M(16)")
        exit(1)
    modrm = int(sys.argv[1], 16)

    mod, reg, rm = convert_modrm(modrm)
    print("MOD:", format(mod, "02b"))
    print("REG:", format(reg, "03b"))
    print("R/M:", format(rm,  "03b"))
    print("address: ", format_mod_rm(mod, rm))
    print("register:", format_reg(reg))



if __name__ == "__main__":
    main()
