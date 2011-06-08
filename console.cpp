#include "common.h"

#define COLUMNS                 80
#define LINES                   24
#define ATTRIBUTE               7
#define VIDEO_RAM               0xB8000
#define VIDEO_CHR(r,c)          vram[(COLUMNS*(r) + (c))*2]
#define VIDEO_ATT(r,c)          vram[(COLUMNS*(r) + (c))*2 + 1]

static int xpos;
static int ypos;
static volatile unsigned char *vram = (unsigned char *) VIDEO_RAM;

void cls()
{
  int i;
  for (i = 0; i < COLUMNS * LINES * 2; ++i)
    vram[i] = 0;
  xpos = ypos = 0;
}

void push_up()
{
  unsigned int r, c;
  for (r = 1; r < LINES; ++r)
    for (c = 0; c < COLUMNS; ++c)
    {
      VIDEO_CHR(r - 1, c) = VIDEO_CHR(r, c);
      VIDEO_ATT(r - 1, c) = VIDEO_ATT(r, c);
    }
  for (c = 0; c < COLUMNS; ++c)
  {
    VIDEO_CHR(LINES - 1, c) = 0;
    VIDEO_ATT(LINES - 1, c) = 0;
  }
}

void newline()
{
  if (ypos + 1 >= LINES)
    push_up();
  else
    ++ypos;
  xpos = 0;
}

void kputchar(int c)
{
  if (c == '\n' || c == '\r')
    newline();
  else
  {
    VIDEO_CHR(ypos, xpos) = c & 0xFF;
    VIDEO_ATT(ypos, xpos) = ATTRIBUTE;
    if (++xpos >= COLUMNS)
      newline();
  }
}

void kputs(const char *s)
{
  kprintf("%s\n", s);
}

void kprintf(const char *format, ...)
{
  char **arg = (char **) &format;
  int c;
  char buf[20]; // FIXME: appropriate buf size?
  ++arg;

  while ((c = *format++) != 0)
  {
    if (c != '%')
      kputchar(c);
    else
    {
      char *p;

      c = *format++;
      switch (c)
      {
        case 'd':
        case 'u':
        case 'x':
          itoa(buf, c, *((int *) arg++));
          p = buf;
          goto string;

        case 's':
          p = *arg++;
          if (!p)
            p = "(null)";

        string:
          while (*p)
            kputchar(*p++);
          break;

        default:
          kputchar(*((int *) arg++));
          break;
      }
    }
  }
}
