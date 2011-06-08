#include "common.h"

#define MAX_BLOCKS 500

typedef struct {
  void *start;
  size_t len;
} MemBlock;

MemBlock available_blocks[MAX_BLOCKS];
int num_available_blocks = 0;

void *raw_malloc(size_t len)
{
  unsigned int i;
  for (i = 0; i < num_available_blocks; ++i)
    if (available_blocks[i].len >= len)
    {
      void *mem = available_blocks[i].start;
      available_blocks[i].start += len;
      available_blocks[i].len -= len;
      return mem;
    }
  panic("malloc failed");
}

void raw_free(void *start, size_t len)
{
  if (num_available_blocks >= MAX_BLOCKS)
    return; // can't take more blocks
  MemBlock *b = &available_blocks[num_available_blocks++];
  b->start = start; b->len = len;
}

void *kmalloc(size_t len)
{
  void *mem = raw_malloc(len + sizeof(size_t));
  *((size_t *) mem) = len;
  return mem + sizeof(size_t);
}

void kfree(void *start)
{
  size_t len = ((size_t *) start)[-1];
  raw_free(start - sizeof(size_t), len + sizeof(size_t));
}

void kmemcpy(void *dst, const void *src, size_t len)
{
  int i;
  for (i = 0; i < len; ++i)
    ((char *) dst)[i] = ((char *) src)[i];
}

void kmemset(void *mem, int value, size_t num)
{
  int i;
  for (i = 0; i < num; ++i)
    ((char *) mem)[i] = value;
}

int kstrcmp(const char *s1, const char *s2)
{
  while (*s1 == *s2)
  {
    if (*s1 == 0)
      return 0;
    ++s1; ++s2;
  }
  return *(const unsigned char *) s1
       - *(const unsigned char *) s2;
}

bool kstreq(const char *s1, const char *s2)
{
  return kstrcmp(s1, s2) == 0;
}
