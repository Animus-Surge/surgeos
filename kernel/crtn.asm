; SurgeOS crtn.S
; C runtime termination

section .init
    pop ebp
    ret

section .fini
    pop ebp
    ret
