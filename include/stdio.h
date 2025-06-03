/**
 * SurgeOS include/stdio.h
 * Standard Input/Output header
 */

#ifndef SURGEOS_STDIO_H
#define SURGEOS_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#define FILENAME_MAX 512
#define BUFSIZ 1024
#define FOPEN_MAX 20
#define L_tmpnam 20
#define L_ctermid 20
#define L_cuserid 20    // Deprecated
#define TMP_MAX 238328  // 26^5, assuming 5-character temporary filenames
#define EOF (-1)
#define NULL ((void*)0)

#define P_tmpdir "/tmp/"

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IOFBF 0x0000  // Full buffering
#define _IOLBF 0x0040  // Line buffering
#define _IONBF 0x0004  // No buffering

// File flags
#define FILE_READ       (1 << 0)
#define FILE_WRITE      (1 << 1)
#define FILE_EOF        (1 << 2)
#define FILE_ERR        (1 << 3)
#define FILE_BUF_ALLOC  (1 << 4)
#define FILE_APPEND     (1 << 5)
#define FILE_DIRTY      (1 << 6)

typedef struct _File FILE;
typedef long fpos_t;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

extern FILE streams[FOPEN_MAX];

// Character I/O
//Output
int putchar(int c);
int putc(int c, FILE* stream);
int fputc(int c, FILE* stream);
int fputs(const char* str, FILE* stream);
int puts(const char* str);
int putc_unlocked(int c, FILE* stream);
int putchar_unlocked(int c);

int ungetc(int c, FILE* stream);

//Input
int getchar(void);
int getc(FILE* stream);
int fgetc(FILE* stream);
char* fgets(FILE* stream);
char* gets(FILE* stream);
int getc_unlocked(FILE* stream);
int getchar_unlocked(void);

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
int ftrylockfile(FILE* stream);
int flockfile(FILE* stream);
void funlockfile(FILE* stream);

// Binary I/O
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);

// Error handling
void clearerr(FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);
void perror(const char* s);

// Buffer management
void setbuf(FILE* stream, char* buf);
void setvbuf(FILE* stream, char* buf, int mode, size_t size);

// Temporary files
char* tmpnam(char* str);
FILE* tmpfile(void);
char* tempnam(const char* dir, const char* prefix);

// Other
int fileno(FILE* stream);
char* ctermid(char* str);
char* cuserid(char* str); // Deprecated, use getlogin() instead

// Internal
int fprint(FILE* stream, const char* buf);

#endif // SURGEOS_STDIO_H

