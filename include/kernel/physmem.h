/**
 * SurgeOS kernel physmem.h
 * Physical memory header
 */

#ifndef SURGEOS_PHYSMEM_H
#define SURGEOS_PHYSMEM_H

#include <sys/cdefs.h>
#include <stdbool.h>
#include <stdint.h>

__EXTC

#define PMM_PAGE_SIZE 4096

void pmm_init(void*, uint32_t);
uintptr_t pmm_alloc_frame(void);
void pmm_free_frame(uintptr_t);
uintptr_t pmm_get_total_memory(void);
uintptr_t pmm_get_used_memory(void);

__EXTC_END

#endif // SURGEOS_PHYSMEM_H
