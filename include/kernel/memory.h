/**
 * SurgeOS kernel memory.h
 * Physical memory and paging functions
 */

#ifndef SURGEOS_MEMORY_H
#define SURGEOS_MEMORY_H

#include <kernel/multiboot.h>

#include <sys/cdefs.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 4096
#define PAGE_ENTRIES 1024

#define PAGE_ALIGN_UP(x) (((x) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))
#define PAGE_ALIGN_DOWN(x) ((x) & ~(PAGE_SIZE - 1))

#define PAGE_OFFSET(addr) ((addr) & 0xFFF)
#define PAGE_DIR_INDEX(addr) (((addr) >> 22) & 0x3FF)
#define PAGE_TABLE_INDEX(addr) (((addr) >> 12) & 0x3FF)

#define PAGE_PRESENT 0x1
#define PAGE_RW      0x2
#define PAGE_USER    0x4

// Paging structures 
typedef struct {
  uint32_t present : 1;
  uint32_t rw : 1;
  uint32_t user : 1;
  uint32_t write_through : 1;
  uint32_t cache_disabled : 1;
  uint32_t accessed : 1;
  uint32_t dirty : 1;
  uint32_t pat : 1;
  uint32_t global : 1;
  uint32_t ignored : 3;
  uint32_t frame : 20;
} __surgeos_packed pt_entry_t;

typedef struct {
  pt_entry_t entries[1024];
} __surgeos_aligned(4096) pt_t;

typedef struct {
  uint32_t present : 1;
  uint32_t rw : 1;
  uint32_t user : 1;
  uint32_t write_through : 1;
  uint32_t cache_disabled : 1;
  uint32_t accessed : 1;
  uint32_t reserved : 1;
  uint32_t page_size : 1;
  uint32_t ignored : 1;
  uint32_t avail : 3;
  uint32_t frame : 20;
} __surgeos_packed pd_entry_t;

typedef struct {
  pd_entry_t entries[1024];
} __surgeos_aligned(4096) pd_t;

// Physical memory functions
void    mem_init            (struct mb_tag_mmap*);
void   *mem_alloc           (void);
void    mem_free            (void*);
void    mem_mark_range      (uintptr_t, size_t, bool);
int     mem_is_free         (void*);
size_t  mem_total_pages     (void);
size_t  mem_used_pages      (void);

// Virtual memory functions (paging)
void    vmem_init           (void);
bool    vmem_map            (uintptr_t, uintptr_t, uint32_t);
bool    vmem_map_range      (uintptr_t, uintptr_t, size_t, uint32_t);
void    vmem_unmap          (uintptr_t);
void   *vmem_get_phys       (void*);

extern void _paging_enable(uintptr_t);

#endif
