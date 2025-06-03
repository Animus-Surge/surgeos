/**
 * SurgeOS kernel paging.h
 * Paging system declarations
 */

#ifndef SURGEOS_PAGING_H
#define SURGEOS_PAGING_H

#include <sys/cdefs.h>

#include <stdint.h>

__EXTC

#define NULL ((void*)0)

// Page table entries

#define PTE_FLAG_PRESENT       (1ULL << 0)
#define PTE_FLAG_RW            (1ULL << 1)
#define PTE_FLAG_USER_SUP      (1ULL << 2)
#define PTE_FLAG_WRITETHROUGH  (1ULL << 3)
#define PTE_FLAG_CACHE_DISABLE (1ULL << 4)
#define PTE_FLAG_ACCESSED      (1ULL << 5)
#define PTE_FLAG_DIRTY         (1ULL << 6)
#define PTE_FLAG_PAGE_ATTR_TAB (1ULL << 7)
#define PTE_FLAG_GLOBAL        (1ULL << 8)
#define PTE_FLAG_AVAIL_1       (1ULL << 9)
#define PTE_FLAG_AVAIL_2       (1ULL << 10)
#define PTE_FLAG_AVAIL_3       (1ULL << 11)

#define PTE_FLAG_NO_EXEC       (1ULL << 63)

typedef uint64_t page_table_entry_t;

#define PTE_GET_PHYS_ADDR(pte) ((pte) & 0x00000FFFFFFFF000ULL)
#define PTE_SET_PHYS_ADDR(pte, addr) \
  ((pte) = ((pte) & 0xFFF0000000000FFFULL | ((addr) & 0x00000FFFFFFFF000ULL)))

// Page directory entries

#define PDE_FLAG_PAGE_SIZE (1ULL << 7)

typedef uint64_t page_directory_entry_t;

#define PDE_GET_PHYS_ADDR_4K(pde) ((pde) & 0x00000FFFFFFFFF000ULL)
#define PDE_GET_PHYS_ADDR_2M(pde) ((pde) & 0x00000FFFFFFFFE00000ULL)

#define PDE_SET_PHYS_ADDR_4K(pde, addr) \
  ((pde) = ((pde) & 0xFFF0000000000FFFULL) | ((addr) & 0x00000FFFFFFFFF000ULL))
#define PDE_SET_PHYS_ADDR_2M(pde, addr) \
  ((pde) = ((pde) & 0xFFF0000000001FFFFFULL) | ((addr) & 0x00000FFFFFFFFE00000ULL))

// Page directory pointer table entries

typedef uint64_t pdpt_entry_t;

#define PDPTE_GET_PHYS_ADDR(pdpte) ((pdpte) & 0x00000FFFFFFFF000ULL)
#define PDPTE_SET_PHYS_ADDR(pdpte, addr) \
  ((pdpte) = ((pdpte) & 0xFFF0000000000FFFULL) | ((addr) & 0x00000FFFFFFFF000ULL))

extern pdpt_entry_t* kernel_pdpt_phys;

void init_paging(void);
void map_page(uint32_t, uint32_t, uint32_t);

__EXTC_END

#endif // SURGEOS_PAGING_H
