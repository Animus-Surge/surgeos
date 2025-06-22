# SurgeOS libk CMakeLists.txt
# Libk; kernel c library

set(SURGEOS_LIBK_SOURCES
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

  # stdio.h
  stdio/printf.c
  stdio/vsnprintf.c

  # string.h
  string/memcmp.c
  string/memcpy.c
  string/memmove.c
  string/memset.c
  string/strcmp.c
  string/strcpy.c
  string/strlen.c
  string/strncat.c
  string/strncpy.c
  string/strtok.c

  # stdlib.h
  stdlib/abort.c
  stdlib/itoa.c
  stdlib/panic.c

  # misc
  formatting.c
)

add_library(surgeos_libk OBJECT
  ${SURGEOS_LIBK_SOURCES}
)

if (surgeos_build_kernel)
  target_compile_options(surgeos_libk PRIVATE -D__surgeos_libk__)
endif()

target_include_directories(surgeos_libk PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
)
