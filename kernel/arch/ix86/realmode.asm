; SurgeOS kernel realmode.asm
; Handles the real mode to protected mode transition

[BITS 32]

extern _protected_mode

GLOBAL _gdt_load

_gdt_load:
    cli

    mov ebx, [esp+4]
    lgdt [ebx]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode

protected_mode:
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax

    jmp _protected_mode

