;; SurgeOS kernel ix86/paging.asm
;; Kernel paging functions (assembly)

bits 32
section .text
global _paging_enable

_paging_enable:
  mov eax, [esp + 4]  ; Get the page directory address from the stack
  mov cr3, eax        ; Load the page directory into CR3

  mov eax, cr0        ; Read the current value of CR0
  or eax, 0x80000000  ; Set the PG (paging) bit in CR0
  mov cr0, eax        ; Write the modified value back to CR0

  ret                 ; Return from the function
