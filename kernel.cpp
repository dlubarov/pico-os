#include "icxxabi.h"
#include "multiboot.h"
#include "common.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

extern "C" unsigned long start_ctors, end_ctors, start_dtors, end_dtors;

class Test
{
  int x;

public:
  Test(int _x)
  {
    x = _x;
  }

  void foo()
  {
    kprintf("foo %d\n", x);
  }

  ~Test()
  {
    kprintf("destructor\n");
  }
};

Test test1(42), test2(100);

void kmain(unsigned long magic, unsigned long addr)
{
  // Am I booted by a Multiboot-compliant boot loader?
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    kprintf("Invalid magic number: 0x%x\n", (unsigned) magic);
    return;
  }

  multiboot_info_t *mbi = (multiboot_info_t *) addr;
  cls();

  if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5))
  {
    kprintf("Both bits 4 and 5 are set.\n");
    return;
  }

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
        addr = (char *) addr + 1;
        --len;
      }
      raw_free(addr, len);
    }
  }
  else
    panic("no memory map was provided");

  int i, j;
  for (i = 0; i < 10; ++i)
  {
    int l = i % 5 + 1;
    char *s = (char *) raw_malloc(l + 1);
    for (j = 0; j < l; ++j)
      s[j] = 'A' + j;
    s[l] = 0;
    raw_free(s, l + 1);
    kprintf("%s\n", s);
  }
  test1.foo();
  test2.foo();
}

extern "C" void loader(unsigned long magic, unsigned long addr)
{
  for (unsigned long *constructor(&start_ctors); constructor < &end_ctors; ++constructor)
    ((void (*) (void)) (*constructor)) ();
  kmain(magic, addr);
  for (unsigned long *destructor(&start_dtors); destructor < &end_dtors; ++destructor)
    ((void (*) (void)) (*destructor)) ();
}
