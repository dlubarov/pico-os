#include "console.h"

void panic(char *message)
{
  cls();
  printf("kernel panic!\n\n");
  printf("%s\n", message);
  hang();
}

void hang()
{
  for (;;)
    asm("hlt");
}
