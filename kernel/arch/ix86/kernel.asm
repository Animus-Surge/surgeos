; ----------------------
; Multiboot Header
; ----------------------

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

; ----------------------
; Stack
; ----------------------

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

; ----------------------
; Entry Point
; ----------------------

extern kernel_main
extern init_gdt
extern init_idt
extern _init

section .text
global kernel_init
kernel_init:
    ; Set up the stack pointer
    mov esp, stack_top

    call init_gdt

global _protected_mode
_protected_mode:
    ; call init_idt
    ; call _init
    call kernel_main

    ; Halt forever
.hang:
    cli
    hlt
    jmp .hang
