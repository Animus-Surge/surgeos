/**
 * SurgeOS include/stdio.h
 * stdio.h
 */

#ifndef SURGEOS_STDIO_H
#define SURGEOS_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#define EOF (-1)
#define NULL ((void*)0)

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef struct _File FILE;
typedef long fpos_t;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

// Character I/O
//Output
int putchar(int c);
int putc(int c, FILE* stream);
int fputc(int c, FILE* stream);
int fputs(const char* str, FILE* stream);
int puts(const char* str);

int ungetc(int c, FILE* stream);

int getchar(void);
int getc(FILE* stream);
int fgetc(FILE* stream);
char* fgets(FILE* stream);
char* gets(FILE* stream);

// Formatted I/O
int printf(const char* __restrict format, ...);
int fprintf(FILE* stream, const char* __restrict format, ...);
int sprintf(char* buf, const char* __restrict format, ...);
int snprintf(char* buf, size_t size, const char* __restrict format, ...);
int vprintf(const char* __restrict format, va_list ap);
int vfprintf(FILE* stream, const char* __restrict format, va_list ap);
int vsprintf(char* buf, const char* __restrict format, va_list ap);
int vsnprintf(char* buf, size_t size, const char* __restrict format, va_list ap);

// File access
FILE* fopen(const char* filename, const char* mode);
FILE* freopen(const char* filename, const char* mode, FILE* stream);
int fclose(FILE* stream);
void rewind(FILE* stream);
int fflush(FILE* stream);
int fseek(FILE* stream, long offset, int whence);
long ftell(FILE* stream);
int fgetpos(FILE* stream, fpos_t* pos);
int fsetpos(FILE* stream, const fpos_t* pos);

// Binary I/O
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);

// Error handling
void clearerr(FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);
void perror(const char* s);

#endif // SURGEOS_STDIO_H

