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
