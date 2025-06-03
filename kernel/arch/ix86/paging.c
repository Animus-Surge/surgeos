/**
 * SurgeOS kernel ix86/paging.c
 * ix86 paging implementation, C functions
 */

#include <kernel/paging.h>

#include <stdint.h>

pdpt_entry_t* kernel_pdpt_phys = NULL;


