; SurgeOS kernel ix86/boot.asm
; ix86 boot assembly

; Multiboot Header
MB_ALIGN        equ 1 << 0
MB_MEMINFO      equ 1 << 1
MB_FLAGS        equ MB_ALIGN | MB_MEMINFO
MB_HEADER_MAGIC equ 0x1BADB002
MB_CHECKSUM     equ -(MB_HEADER_MAGIC + MB_FLAGS)

section .multiboot
align 4
    dd MB_HEADER_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

; Stack
section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
; Helpers

; Entry Point
extern kernel_main
extern init_gdt
extern _init

global _boot
_boot:
    ; Set up the stack pointer
    mov esp, stack_top

    ; Setup Global Descriptor Table
    call init_gdt

    ; Jump to protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode

[bits 32]
protected_mode:
    ; Set segment registers
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax

    ; Enable paging

    call kernel_main

    ; Halt forever
.hang:
    cli
    hlt
    jmp .hang
