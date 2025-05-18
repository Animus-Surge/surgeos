cmake_minimum_required(VERSION 3.0)

project(surgeos 
  VERSION 0.1
  LANGUAGES C ASM_NASM)

add_subdirectory(kernel)
add_subdirectory(libc)

add_executable(surgeos.bin
  $<TARGET_OBJECTS:surgeos_kernel>
  $<TARGET_OBJECTS:surgeos_libc>
)
target_link_options(surgeos.bin PRIVATE
  -T ${CMAKE_SOURCE_DIR}/linker.ld
)

