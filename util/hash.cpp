#include "hash.h"

unsigned int hash_string(const char *s)
{
  int n = 0;
  while (*s != 0)
  {
    n = n * 17 ^ *s;
    ++s;
  }
  return n;
}
