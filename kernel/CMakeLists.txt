# SurgeOS Kernel.cmake
# Kernel cmake module; builds the kernel for SurgeOS

enable_language(ASM_NASM)

set(SURGEOS_KERNEL_SOURCES
  arch/ix86/kernel.asm
  arch/ix86/realmode.asm
  arch/ix86/isr.asm
  arch/ix86/crti.asm
  arch/ix86/crtn.asm
  arch/ix86/paging.asm
  arch/ix86/gdt.c
  arch/ix86/idt.c
  arch/ix86/isr.c
  arch/ix86/paging.c
  arch/ix86/tty.c
  
  driver/keyboard.c
  driver/vga.c

  kernel.c
  syscall.c
)

add_library(surgeos_kernel OBJECT
  ${SURGEOS_KERNEL_SOURCES}
)

target_include_directories(surgeos_kernel PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)
