;; SurgeOS kernel ix86/paging.asm
;; ix86 paging implementation

global load_page
load_page:
    mov eax, [esp + 4]
    mov cr3, eax
    ret

global start_paging
start_paging:
    mov eax, cr0
    or eax, 0x00000010
    mov cr0, eax
    ret
