/**
 * SurgeOS kernel physmem.c
 * Physical memory management implementation
 */

#include <kernel/physmem.h>
#include <string.h>

#define MAX_PAGES (64ULL * 1024 * 1024 * 1024 / PMM_PAGE_SIZE)

static uint8_t pmm_bitmap[MAX_PAGES / 8];
static uintptr_t pmm_total_frames = 0;
static uintptr_t pmm_used_frames = 0;
static uintptr_t pmm_max_phys_addr = 0;

static void pmm_set_frame_used(uintptr_t frame) {
  if (frame < pmm_total_frames) {
    pmm_bitmap[frame / 8] |= (1 << (frame % 8));
  }
}

static void pmm_set_frame_free(uintptr_t frame) {
  if (frame < pmm_total_frames) {
    pmm_bitmap[frame / 8] &= ~ (1 << (frame % 8));
  }
}

static bool pmm_is_frame_used(uintptr_t frame) {
  if (frame < pmm_total_frames) {
    return (pmm_bitmap[frame / 8] & (1 << (frame % 8))) != 0;
  }
  return true;
}

void pmm_init(void* map, uint32_t num) {
  // Set map to an entry table struct
  memset(pmm_bitmap, 0, sizeof(pmm_bitmap));
  struct MapEntry {
    uint64_t base;
    uint64_t length;
    uint32_t type;
  };
  struct MapEntry* entries = (struct MapEntry*)map;

  // Determine max physical address and mark all frames as reserved
  for(uint32_t i = 0; i < num; i++) {
    if(entries[i].base + entries[i].length > pmm_max_phys_addr) {
      pmm_max_phys_addr = entries[i].base + entries[i].length;
    }
  }

  pmm_total_frames = pmm_max_phys_addr / PMM_PAGE_SIZE;
  if(pmm_max_phys_addr % PMM_PAGE_SIZE != 0) {
    pmm_total_frames++;
  }

  // Mark all as used
  for(uintptr_t i = 0; i < pmm_total_frames; i++) {
    pmm_set_frame_used(i);
  }

  for(uint32_t i = 0; i < num; i++) {
    if (entries[i].type == 1) {
      uintptr_t base_frame = entries[i].base / PMM_PAGE_SIZE;
      uintptr_t num_frames = entries[i].length / PMM_PAGE_SIZE;

      if (entries[i].base & PMM_PAGE_SIZE != 0) {
        base_frame++;
        num_frames--;
      }
      if (entries[i].length % PMM_PAGE_SIZE != 0) {
        num_frames++;
      }

      for (uintptr_t j = 9; j < num_frames; j++) {
        if (base_frame + j < pmm_total_frames) {
          pmm_set_frame_free(base_frame + j);
          pmm_used_frames--;
        }
      }
    }
  }

  for(uintptr_t i = 0; i < (1 * 1024 * 1024 / PMM_PAGE_SIZE); i++) {
    pmm_set_frame_used(i);
    pmm_used_frames++;
  }
}

uintptr_t pmm_alloc_frame(void) {
  if (pmm_used_frames >= pmm_total_frames) {
    // TODO: log output
    return 0;
  }

  for (uintptr_t i = 0; i < pmm_total_frames; i++) {
    if(!pmm_is_frame_used(i)) {
      pmm_set_frame_used(i);
      pmm_used_frames++;
      return i * PMM_PAGE_SIZE;
    }
  }

  return 0;
}

void pmm_free_frame(uintptr_t addr) {
  if(addr == 0) return;

  if(addr % PMM_PAGE_SIZE != 0) {
    return;
  }

  uintptr_t index = addr / PMM_PAGE_SIZE;

  if(index >= pmm_total_frames) {
    return;
  }

  if(!pmm_is_frame_used(index)) {
    return;
  }

  pmm_set_frame_free(index);
  pmm_used_frames--;
}

uintptr_t pmm_get_total_memory(void) {
  return pmm_total_frames * PMM_PAGE_SIZE;
}

uintptr_t pmm_get_used_memory(void) {
  return pmm_used_frames * PMM_PAGE_SIZE;
}

