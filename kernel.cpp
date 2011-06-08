#include "icxxabi.h"
#include "multiboot.h"
#include "common.h"
#include "util/hashmap.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

extern "C" unsigned long start_ctors, end_ctors, start_dtors, end_dtors;
void test_all();

void kmain(multiboot_info_t *mbi)
{
  cls();
  test_all();
}

void init_memory(multiboot_info_t *mbi)
{
  if (CHECK_FLAG(mbi->flags, 6))
  {
    memory_map_t *mmap;
    for (mmap = (memory_map_t *) mbi->mmap_addr;
         (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
         mmap = (memory_map_t *) ((unsigned long) mmap
                                  + mmap->size + sizeof (mmap->size)))
    {
      void *addr = (void *) mmap->base_addr_low;
      size_t len = mmap->length_low;
      if (addr == 0)
      {
        // We don't want malloc to return 0! Skip that byte.
        addr = (char *) addr + 4;
        len -= 4;
      }
      raw_free(addr, len);
    }
  }
  else
    panic("no memory map was provided");
}

extern "C" void loader(unsigned long magic, unsigned long addr)
{
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    panic("bootloader did not supply multiboot magic number");
  multiboot_info_t *mbi = (multiboot_info_t *) addr;
  if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5))
    panic("Both bits 4 and 5 are set.");

  init_memory(mbi);

  for (unsigned long *constructor(&start_ctors); constructor < &end_ctors; ++constructor)
    ((void (*) (void)) (*constructor))();

  kmain(mbi);

  for (unsigned long *destructor(&start_dtors); destructor < &end_dtors; ++destructor)
    ((void (*) (void)) (*destructor))();
}
