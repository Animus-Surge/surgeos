; SurgeOS kernel ix86/boot.asm
; ix86 boot assembly

; Multiboot2 Header
MB_HEADER_MAGIC    equ 0xe85250d6
MB_ARCH            equ 0x00
MB_HEADER_LENGTH   equ mb_end - mb_begin
MB_CHECKSUM        equ -(MB_HEADER_MAGIC + MB_ARCH + MB_HEADER_LENGTH)

section .multiboot
align 8
mb_begin:
    ; Primary Multiboot2 header
    dd MB_HEADER_MAGIC
    dd MB_ARCH
    dd MB_HEADER_LENGTH
    dd MB_CHECKSUM

    ; Framebuffer tag
    dw 5    ; Tag type: framebuffer
    dw 0    ; flags
    dd 36   ; size
    dd 1024 ; width
    dd 768  ; height
    dd 32   ; depth
    dd 0    ; padding
    db 16   ; red position
    db 8    ; green position
    db 0    ; blue position
    db 0    ; reserved

    ; End tag
    dw 0    ; Tag type: end
    dw 0    ; flags
    dd 8    ; size
mb_end:

; Stack
section .bss
align 16
global stack_bottom, stack_top

stack_bottom:
    resb 16384
stack_top:

; multiboot info
section .data
align 8
    mb_magic_ptr resd 1 ; Pointer to multiboot magic number
    mb_info_ptr  resd 1 ; Pointer to multiboot info structure

section .text
; Helpers

; Entry Point
extern kernel_main
extern kernel_init
extern init_gdt

global _boot
_boot:
    ; Set up the stack pointer
    mov esp, stack_top

    ; Store multiboot magic and info pointers
    mov [mb_magic_ptr], eax
    mov [mb_info_ptr], ebx

    ; Initialize gdt
    call init_gdt
    jmp 0x08:fullstart

fullstart:
    ; Reload the multiboot magic and info pointers
    mov eax, [mb_magic_ptr]
    mov ebx, [mb_info_ptr]
    
    ; Call the kernel main function
    push ebx
    push eax
    call kernel_init

    ; TODO: CRT initialization
    ; TODO: kernel_main

