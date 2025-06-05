; SurgeOS kernel realmode.asm
; Handles the real mode to protected mode transition

[bits 32]

extern _protected_mode
global _gdt_load
_gdt_load:
    cli

    mov ebx, [esp+4]
    lgdt [ebx]

    ret

