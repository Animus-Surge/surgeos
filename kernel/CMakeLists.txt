# SurgeOS Kernel.cmake
# Kernel cmake module; builds the kernel for SurgeOS

enable_language(ASM_NASM)

set(SURGEOS_KERNEL_SOURCES
  arch/ix86/boot.asm
  arch/ix86/crti.asm
  arch/ix86/crtn.asm
  arch/ix86/gdt.asm
  arch/ix86/isr.asm
  arch/ix86/paging.asm
  arch/ix86/gdt.c
  arch/ix86/idt.c
  arch/ix86/isr.c
  
  driver/framebuffer.c
  driver/keyboard.c
  driver/memory.c
  driver/serial.c
  driver/tty.c

  surgeos/shell/shell.c
  surgeos/shell/clear.c
  surgeos/shell/echo.c
  surgeos/shell/exit.c
  surgeos/shell/help.c
  surgeos/shell/reboot.c

  kernel.c
  kernel_init.c
)

add_library(surgeos_kernel OBJECT
  ${SURGEOS_KERNEL_SOURCES}
)

target_include_directories(surgeos_kernel PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)
