bits 32
section .text

global isr_load
isr_load:
    mov eax, [esp+4] ; Load the address of the IDT
    lidt [eax]      ; Load the IDT
    ret

global isr_default
isr_default:
    pusha
    ; assuming interrupt number is at esp + 32
    mov al, [esp + 32]

    cmp al, 0x28         ; IRQ8 or above?
    jl .send_master

    mov al, 0x20
    out 0xA0, al         ; Send EOI to slave PIC

.send_master:
    mov al, 0x20
    out 0x20, al         ; Send EOI to master PIC

    popa
    iret

extern isr_keyboard_input
global isr_keyboard
isr_keyboard:
    pusha
    xor eax, eax

    in al, 0x60
    push eax
    
    call isr_keyboard_input ; Call the keyboard input Handler

    add esp, 4
    mov al, 0x20
    out 0x20, al         ; Send EOI to master PIC
    
    popa
    iret

extern isr_page_fault_handler
global isr_page_fault
isr_page_fault:
    pusha
    mov eax, [esp + 32] ; Get the error code
    mov ebx, [esp + 36] ; Get the faulting address

    push eax            ; Save error code
    push ebx            ; Save faulting address

    call isr_page_fault_handler ; Call the page fault handler

    add esp, 8          ; Clean up the stack

    mov al, 0x20
    out 0x20, al        ; Send EOI to master PIC

    popa
    iret

global pic_remap
pic_remap:
    ; Save current state
    in al, 0x21
    mov ah, al
    in al, 0xA1
    mov bh, al

    ; Remap the PIC
    mov al, 0x11
    out 0x20, al         ; Start PIC1 initialization
    out 0xA0, al         ; Start PIC2 initialization

    ; Set vector offsets
    mov al, 0x20
    out 0x21, al         ; Set offset for master PIC
    mov al, 0x28
    out 0xA1, al         ; Set offset for slave PIC

    ; Set up cascading
    mov al, 0x04
    out 0x21, al         ; Tell master PIC that slave is at IRQ2
    mov al, 0x02
    out 0xA1, al         ; Tell slave PIC its cascade identity

    ; Set mode (ICW4)
    mov al, 0x01
    out 0x21, al
    out 0xA1, al         ; Set 8086 mode

    ; Restore saved state
    mov al, ah
    out 0x21, al         ; Restore master PIC mask
    mov al, bh
    out 0xA1, al         ; Restore slave PIC mask

    ret




