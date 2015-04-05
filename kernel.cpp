#include "icxxabi.h"
#include "multiboot.h"
#include "common.h"
#include "tar.h"

#define CHECK_FLAG(flags,bit) ((flags) & (1 << (bit)))

extern "C" unsigned long start_ctors, end_ctors, start_dtors, end_dtors;
void test_all();

void kmain(multiboot_info_t *mbi)
{
  if (mbi->mods_count != 1)
    panic("unexpected module count");
  module_t *modules = (module_t *) mbi->mods_addr;
  void *initrd_start = (void *) modules[0].mod_start;
  void *initrd_end = (void *) modules[0].mod_end;
  Blob initrd_blob(initrd_start, initrd_end);
  StringHashMap<Blob> initrd;
  parse_tar(initrd_blob, initrd);
  Blob ttf = initrd["Inconsolata-Regular.ttf"];

  vbe_mode_info_t *vbe_mode_info = (vbe_mode_info_t *) mbi->vbe_mode_info;
  init_graphics(vbe_mode_info);

  int w = vbe_mode_info->Xres, h = vbe_mode_info->Yres;
  for (uint16 x = 0; x < w; ++x)
  {
    for (uint16 y = 0; y < h; ++y)
    {
      int r = x * 255 / w;
      int g = y * 255 / h;
      int b = 180;

      setpixel(x, y, r, g, b);
    }
  }

  cls();
  test_all();
  newline();

  kputs("compiling standard library...");
  ;
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
    panic1("bootloader did not supply multiboot magic number; found %d", magic);
  multiboot_info_t *mbi = (multiboot_info_t *) addr;
  if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5))
    panic("Both bits 4 and 5 are set.");

  if (CHECK_FLAG(mbi->flags, 2))
    kprintf("command = %s\n", (char *) mbi->cmdline);

  init_memory(mbi);

  for (unsigned long *constructor(&start_ctors); constructor < &end_ctors; ++constructor)
    ((void (*) (void)) (*constructor))();

  kmain(mbi);

  for (unsigned long *destructor(&start_dtors); destructor < &end_dtors; ++destructor)
    ((void (*) (void)) (*destructor))();
}
