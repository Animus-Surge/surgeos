# SurgeOS kernel_toolchain.cmake
# This file is used to set up the toolchain for building the SurgeOS kernel.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Cross compiler
set(SURGEOS_CROSS_COMPILER_PATH ".opt/x86_64-elf-7.5.0-Linux-x86_64/bin/")
set(SURGEOS_CROSS_COMPILER_PREFIX "x86_64-elf-")

# Set compiler binaries
set(CMAKE_C_COMPILER "${SURGEOS_CROSS_COMPILER_PATH}${SURGEOS_CROSS_COMPILER_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${SURGEOS_CROSS_COMPILER_PATH}${SURGEOS_CROSS_COMPILER_PREFIX}gcc")
set(CMAKE_ASM_COMPILER "${SURGEOS_CROSS_COMPILER_PATH}${SURGEOS_CROSS_COMPILER_PREFIX}gcc")
set(CMAKE_LINKER "${SURGEOS_CROSS_COMPILER_PATH}${SURGEOS_CROSS_COMPILER_PREFIX}ld")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Compiler flags
set(CMAKE_C_FLAGS "-ffreestanding -Wall -Wextra -nostdlib" 
  CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-ffreestanding -Wall -Wextra -nostdlib -fno-exceptions"
  CACHE STRING "" FORCE)

