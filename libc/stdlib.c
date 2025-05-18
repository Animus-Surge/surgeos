#include <stdlib.h>

#include <stdio.h>
//Future proofing to maybe be able to print stack traces or something


__attribute__((__noreturn__))
void abort(void) {
#if defined(__surgeos_libk__)
    //TODO: panic implementation
    printf("Kernel panic: abort called\n");
    asm volatile("hlt");
#else
    printf("Abort called.\n");
#endif
    while(1) {}
    __builtin_unreachable();
}
