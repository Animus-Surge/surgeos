/**
 * SurgeOS memory.c
 * Kernel memory driver
 */

#include <kernel/memory.h>
#include <kernel/multiboot.h>

#include <drivers/serial.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MEM_ERROR ((void*)-1)

extern void paging_enable(uintptr_t page_dir);

extern char kernel_start, kernel_end;
extern char stack_bottom, stack_top;

// TODO: implement dynamic bitmap allocation
#define MAX_PHYS_MEM (4 * 1024 * 1024) // 4MiB max physical memory
#define PAGE_SIZE 4096 // 4KiB pages
#define MAX_PAGES (MAX_PHYS_MEM / PAGE_SIZE) // Maximum number of pages
#define BITMAP_SIZE ((MAX_PAGES + 7) / 8) // Size of the bitmap in bytes
static uint8_t mem_bitmap[BITMAP_SIZE];

static size_t bitmap_size_bytes = 0;
static size_t total_pages = 0;

static pd_t* kernel_page_dir = NULL; // Kernel page directory

// Bitmap manipulation functions

static inline void set_bit(size_t bit) {
  mem_bitmap[bit / 8] |= (1 << (bit % 8));
}

static inline void clear_bit(size_t bit) {
  mem_bitmap[bit / 8] &= ~(1 << (bit % 8));
}

static inline bool test_bit(size_t bit) {
  return (mem_bitmap[bit / 8] & (1 << (bit % 8)));
}

/**
 * @brief Get page frame number for address
 * @param addr (uintptr_t) the address to get the index for
 * @return the index of the address given
 */
static inline size_t addr_to_index(uintptr_t addr) {
  return addr / PAGE_SIZE;
}

// Physical memory functions

/**
 * @brief Sets a range of bitmap entries
 */
void mem_mark_range(uintptr_t start_addr, size_t len, bool value) {
  serial_printf("Memory: Marking range: 0x%x - 0x%x as %s\n", start_addr, start_addr + len - 1, value ? "used" : "free");
  size_t start = addr_to_index(start_addr);
  size_t end = addr_to_index(start_addr + len - 1);
  for (size_t i = start; i <= end && i < total_pages; i++) {
    if(value) 
      set_bit(i);
    else
      clear_bit(i);
  }
}

/**
 * @brief Initialize the physical memory page
 *
 * Initialize the physical memory system. Creates the bitmap
 * to keep track of memory stuff.
 *
 * @param mb_map (struct mb_tag_mmap*) the multiboot memory map
 * @param bitmap_storage (void*) pointer to the bitmap storage area
 */
void mem_init(struct mb_tag_mmap* mem_map) {
  serial_writes("Memory: Initializing physical memory\n");
  uintptr_t max_addr = 0;
  size_t entry_count = (mem_map->size - sizeof(*mem_map)) / mem_map->entry_size;

  for (size_t i = 0; i < entry_count; i++) {
    struct mb_mmap_entry* entry = &mem_map->entries[i];
    uintptr_t end_addr = entry->addr + entry->len;
    if (end_addr > max_addr) {
      max_addr = end_addr;
    }
  }

  total_pages = max_addr / PAGE_SIZE;
  bitmap_size_bytes = (total_pages + 7) / 8;

  serial_printf("Memory: Total pages: %u, Bitmap size: %u bytes\n", total_pages, bitmap_size_bytes);

  for (size_t i = 0; i < bitmap_size_bytes; i++) {
    mem_bitmap[i] = 0xff;
  }

  for (size_t i = 0; i < entry_count; i++) {
    struct mb_mmap_entry* entry = &mem_map->entries[i];
    if (entry->type == MB_MEM_AVAILABLE) {
      mem_mark_range(entry->addr, entry->len, false);
    }
  }

  set_bit(0); // Mark first page as used (null pointer page)

  // Mark kernel memory as used
  mem_mark_range((uintptr_t)&kernel_start, (uintptr_t)&kernel_end - (uintptr_t)&kernel_start, true);

  serial_printf("Memory: Initialized with %u pages, bitmap size %u bytes\n", total_pages, bitmap_size_bytes);
  serial_printf("Memory: Kernel memory marked as used from 0x%x to 0x%x\n", (uintptr_t)&kernel_start, (uintptr_t)&kernel_end);
  serial_printf("Memory: Bitmap initialized with %u bytes\n", bitmap_size_bytes);
  serial_printf("Memory: Free pages: %u\n", mem_used_pages());
  serial_printf("Memory: Total pages: %u\n", total_pages);
}

/**
 * @brief Allocate a memory page
 *
 * This function allocates a single memory page and returns a pointer to it.
 * It finds the first free page in the bitmap, marks it as used, and returns
 * the corresponding address.
 *
 * @return void* pointer to the allocated memory page
 */
void* mem_alloc(void) {
  for (size_t i = 0; i < total_pages; i++) {
    if (test_bit(i)) {
      continue; // Page is already used
    }
    set_bit(i); // Mark the page as used
    return (void*)(i * PAGE_SIZE); // Return the address of the allocated page
  }
  return MEM_ERROR; // No free pages available ; TODO: error handling
}

/**
 * @brief Free a memory page
 *
 * This function frees a previously allocated memory page.
 * It marks the corresponding page in the bitmap as free.
 *
 * @param ptr (void*) pointer to the memory page to free
 */
void mem_free(void* ptr) {
  if (ptr == NULL) {
    return; // Nothing to free
  }
  
  size_t index = addr_to_index((uintptr_t)ptr);
  if (index < total_pages) {
    clear_bit(index); // Mark the page as free
  }
}

/**
 * @brief Check if a memory address is free
 *
 * This function checks if the given memory address is free.
 * It returns 1 if the address is free, 0 otherwise.
 *
 * @param ptr (void*) the pointer to check
 * @return int 1 if free, 0 if not
 */
int mem_is_free(void* ptr) {
  return test_bit(addr_to_index((uintptr_t)ptr)) ? 0:1;
}

/**
 * @brief Get the total number of pages in memory
 *
 * @return size_t the total number of pages
 */
size_t mem_total_pages(void) {
  return total_pages;
}

/**
 * @brief Get the number of used pages in memory
 * 
 * This function counts the number of used pages in memory.
 * It iterates through the bitmap and counts the pages that are not free.
 * 
 * @return size_t the number of used pages
 */
size_t mem_used_pages(void) {
  size_t used = 0;
  for (size_t i = 0; i < total_pages; i++) {
    if (!test_bit(i)) {
      used++;
    }
  }
  return used;
}

// Virtual memory functions

/**
 * @brief Initialize the virtual memory system
 *
 * This function initializes the virtual memory system.
 * It sets up the necessary structures for paging.
 */
void vmem_init(void) {
  serial_writes("Virtual Memory: Initializing\n");

  kernel_page_dir = (pd_t*)mem_alloc();
  if (kernel_page_dir == MEM_ERROR) {
    serial_writes("Virtual Memory: Failed to allocate page directory\n");
    return; // TODO: handle error
  }

  // Clear all entries in the page directory
  for(size_t i = 0; i < 1024; i++) {
    kernel_page_dir->entries[i].present = 0;
    kernel_page_dir->entries[i].rw = 0;
    kernel_page_dir->entries[i].user = 0;
    kernel_page_dir->entries[i].frame = 0;
  }

  serial_writes("Virtual Memory: Page directory initialized\n");

  // Map the first 4MiB of memory to the first 4MiB of virtual address space
  for(uintptr_t addr = 0x00000000; addr < 0x00400000; addr += 0x1000) {
    vmem_map(addr, addr, PAGE_PRESENT | PAGE_RW);
  }

  // Map the kernel memory
  serial_printf("DEBUG: kernel start address: 0x%x\n", (uintptr_t)&kernel_start);
  serial_printf("DEBUG: kernel end address: 0x%x\n", (uintptr_t)&kernel_end);

  uintptr_t kstart = ((uintptr_t)&kernel_start) & ~0xFFF;
  uintptr_t kend   = ((uintptr_t)&kernel_end + 0xFFF) & ~0xFFF;
  serial_printf("DEBUG: blocked kernel addresses: 0x%x - 0x%x\n", kstart, kend);

  for(uintptr_t addr = kstart; addr < kend; addr += 0x1000) {
    vmem_map(addr, addr, PAGE_PRESENT | PAGE_RW);
  }

  // Map kernel stack
  serial_printf("DEBUG: kernel stack bottom address: 0x%x\n", (uintptr_t)&stack_bottom);
  serial_printf("DEBUG: kernel stack top address: 0x%x\n", (uintptr_t)&stack_top);

  uintptr_t stack_start = ((uintptr_t)&stack_bottom) & ~0xFFF;
  uintptr_t stack_end   = ((uintptr_t)&stack_top + 0xFFF) & ~0xFFF;
  serial_printf("DEBUG: blocked kernel stack addresses: 0x%x - 0x%x\n", stack_start, stack_end);

  for(uintptr_t addr = stack_start; addr < stack_end; addr += 0x1000) {
    vmem_map(addr, addr, PAGE_PRESENT | PAGE_RW);
  }

  serial_printf("Virtual Memory: Kernel mapped to page table at 0x%x\n", (uintptr_t)kernel_page_dir);
  serial_printf("Virtual Memory: Kernel stack mapped to page table at 0x%x\n", (uintptr_t)kernel_page_dir);
  serial_writes("Virtual Memory: Enabling paging\n");

  _paging_enable((uintptr_t)kernel_page_dir);
  serial_writes("Virtual Memory: Paging enabled.\n");
}

/**
 * @brief Map a virtual address to a physical address
 * 
 * @param virt_addr (void*) the virtual address to map
 * @param phys_addr (void*) the physical address to map to
 * 
 * @return void
 * 
 * This function maps a virtual address to a physical address.
 * It sets up the page table entries accordingly.
 */
bool vmem_map(uintptr_t virt_addr, uintptr_t phys_addr, uint32_t flags) {
  size_t pd_index = (virt_addr >> 22) & 0x3ff;
  size_t pt_index = (virt_addr >> 12) & 0x3ff;

  pd_t* pd = kernel_page_dir;
  pt_t* pt;

  if(!pd->entries[pd_index].present) {
    pt = (pt_t*) mem_alloc();
    if(!pt) return false;

    for(size_t i = 0; i < PAGE_ENTRIES; i++) {
      pt->entries[i].frame = 0;
      pt->entries[i].present = 0;
    }

    pd->entries[pd_index].frame = ((uintptr_t)pt) >> 12;
    pd->entries[pd_index].present = 1;
    pd->entries[pd_index].rw = 1;
    pd->entries[pd_index].user = 0;
  } else {
    pt = (pt_t*)((pd->entries[pd_index].frame) << 12);
  }

  pt->entries[pt_index].frame = phys_addr >> 12;
  pt->entries[pt_index].present = (flags & 0x1);
  pt->entries[pt_index].rw = ((flags >> 1) & 0x1);
  pt->entries[pt_index].user = ((flags >> 2) & 0x1);

  return true;  
}

/**
 * @brief Map a range of virtual addresses to physical addresses
 * 
 * @param virt_addr (void*) the starting virtual address to map
 * @param phys_addr (void*) the starting physical address to map to
 * @param size (size_t) the size of the range to map
 * @param flags (uint32_t) flags for the mapping (e.g., PAGE_PRESENT, PAGE_RW)
 * 
 * @return bool true if successful, false otherwise
 * 
 * This function maps a range of virtual addresses to physical addresses.
 */
bool vmem_map_range(uintptr_t virt_addr, uintptr_t phys_addr, size_t size, uint32_t flags) {
  uintptr_t virt = virt_addr & ~0xFFF; // Align to page boundary
  uintptr_t phys = phys_addr & ~0xFFF; // Align to page boundary
  size_t pages = (size + PAGE_SIZE - 1) / PAGE_SIZE; // Calculate number of pages needed
  
  for (size_t i = 0; i < pages; i++) {
    if (!vmem_map(virt, phys, flags)) {
      return false; // If mapping fails, return false
    }

    virt += 0x1000;
    phys += 0x1000;
  }

  return true; // All pages mapped successfully
}

/**
 * @brief Unmap a virtual address
 * 
 * @param virt_addr (void*) the virtual address to unmap
 * 
 * @return void
 * 
 * This function unmaps a virtual address, removing its mapping
 * from the page table.
 */
void vmem_unmap(uintptr_t virt_addr) {
  size_t pd_index = (virt_addr >> 22) & 0x3ff;
  size_t pt_index = (virt_addr >> 12) & 0x3ff;

  pd_t* pd = kernel_page_dir;

  if(!pd->entries[pd_index].present) return;

  pt_t* pt = (pt_t*)(pd->entries[pd_index].frame << 12);

  pt->entries[pt_index].present = 0;
  pt->entries[pt_index].frame = 0;
}

/**
 * @brief Get the physical address corresponding to a virtual address
 * 
 * @param virt_addr (void*) the virtual address to get the physical address for
 * 
 * @return void* the physical address corresponding to the given virtual address
 * 
 * This function retrieves the physical address that corresponds to a given
 * virtual address, if such a mapping exists.
 */
void* vmem_get_phys(void* virt_addr) {
  return NULL; // Placeholder, actual implementation needed
}
