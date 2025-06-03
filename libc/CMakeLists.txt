# SurgeOS Libc.cmake
# LibC cmake module; builds the standard C library for SurgeOS

set(SURGEOS_LIBC_SOURCES
  # ctype.h
  ctype/isalnum.c
  ctype/isalpha.c
  ctype/iscntrl.c
  ctype/isdigit.c
  ctype/isgraph.c
  ctype/islower.c
  ctype/isprint.c
  ctype/ispunct.c
  ctype/isspace.c
  ctype/isupper.c
  ctype/isxdigit.c
  ctype/toupper.c
  ctype/tolower.c

  # errno.h
  errno/errno.c

  # stdio.h
  stdio/fflush.c
  stdio/fprintf.c
  stdio/fputc.c
  stdio/printf.c
  stdio/putc.c
  stdio/putchar.c
  stdio/puts.c
  stdio/stdio.c
  stdio/vfprintf.c

  # string.h
  string/memcmp.c
  string/memcpy.c
  string/memmove.c
  string/memset.c
  string/strlen.c

  # stdlib.h
  stdlib/abort.c
  stdlib/exit.c

  # unistd.h
  unistd/_exit.c
  unistd/read.c
  unistd/write.c
)

add_library(surgeos_libc OBJECT
  ${SURGEOS_LIBC_SOURCES}
)

if (surgeos_build_kernel)
  target_compile_options(surgeos_libc PRIVATE -D__surgeos_libk__)
endif()

target_include_directories(surgeos_libc PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)
