#include "common.h"

void hang()
{
  for (;;)
    asm("hlt");
}

void panic(const char *message)
{
  cls();
  kprintf("kernel panic!\n\n");
  kprintf("%s\n", message);
  hang();
}
