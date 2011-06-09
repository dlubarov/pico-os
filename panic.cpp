#include "common.h"

void hang()
{
  for (;;)
    asm("hlt");
}

void panic(const char *message)
{
  cls();
  kputs("kernel panic!\n\n");
  kprintf("%s\n", message);
  hang();
}

void panic1(const char *format, int a)
{
  cls();
  kputs("kernel panic!\n\n");
  kprintf(format, a);
  hang();
}

void panic2(const char *format, int a, int b)
{
  cls();
  kputs("kernel panic!\n\n");
  kprintf(format, a, b);
  hang();
}
