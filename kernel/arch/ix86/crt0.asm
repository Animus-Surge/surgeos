;; SurgeOS ix86 kernel crt0
;; Program initialization code

section .text
global _start

_start:
    ; Stack frame setup
    movl $0, %esp
    pushl %ebp
    pushl %ebp
    movl %esp, %ebp

    pushl %esi
    pushl %edi

    call init_stdlib

    movl $0, %eax
    movl %eax, %edx
    movl %eax, %ecx

    call _init

    popl %edi
    popl %esi

    movl %eax, %edi
    call exit
size _start, _start - _start
