# SurgeOS Kernel.cmake
# Kernel cmake module; builds the kernel for SurgeOS

enable_language(ASM_NASM)

set(SURGEOS_KERNEL_SOURCES
  driver/keyboard.c
  kernel.c
  tty.c
  gdt.c
  idt.c
  isr.c
  isr.asm
  realmode.asm
  kernel.asm
  crti.asm
  crtn.asm
)

add_library(surgeos_kernel OBJECT
  ${SURGEOS_KERNEL_SOURCES}
)

target_include_directories(surgeos_kernel PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)
