# SurgeOS Libc.cmake
# LibC cmake module; builds the standard C library for SurgeOS

set(SURGEOS_LIBC_SOURCES
  # stdio.h
  stdio/printf.c
  stdio/putchar.c
  stdio/puts.c

  # string.h
  string/memcmp.c
  string/memcpy.c
  string/memmove.c
  string/memset.c
  string/strlen.c

  # stdlib.h
  stdlib/abort.c
)

add_library(surgeos_libc OBJECT
  ${SURGEOS_LIBC_SOURCES}
)

target_compile_options(surgeos_libc PRIVATE -D__surgeos_libk__)

target_include_directories(surgeos_libc PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)
