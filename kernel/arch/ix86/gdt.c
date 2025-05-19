/** SurgeOS kernel gdt.c
 * Global Descriptor Table (GDT) implementation
 */

#include <kernel/kernel.h>

static gdt_entry_t gdt_entries[3];
static gdt_ptr_t gdt_ptr;

void init_gdt() {
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
  gdt_ptr.base = (uint32_t)&gdt_entries;

  // Null segment
  gdt_entries[0] = (gdt_entry_t){0}; 

  // Code segment
  gdt_entries[1].base_low = 0;
  gdt_entries[1].base_middle = 0;
  gdt_entries[1].base_high = 0;
  gdt_entries[1].limit_low = 0xFFFF;
  gdt_entries[1].granularity = 0xCF; // 4K granularity, 32-bit
  gdt_entries[1].access = 0x9A; // Present, ring 0, executable, readable

  // Data segment
  gdt_entries[2].base_low = 0;
  gdt_entries[2].base_middle = 0;
  gdt_entries[2].base_high = 0;
  gdt_entries[2].limit_low = 0xFFFF;
  gdt_entries[2].granularity = 0xCF; // 4K granularity, 32-bit
  gdt_entries[2].access = 0x92; // Present, ring 0, writable

  _gdt_load(&gdt_ptr);
}
