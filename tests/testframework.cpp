#include "testframework.h"
#include "../common.h"

#define DEFAULT_MESSAGE "<no message>"

void test_category(const char *cat)
{
  kprintf("testing %s...\n", cat);
}

void assert(bool c, const char *message)
{
  if (!c)
  {
    kprintf("FAILURE: %s\n", message);
    if (STOP_ON_FAILURE)
      hang();
  }
}

void assert(bool c)
{
  assert(c, DEFAULT_MESSAGE);
}

void assert_false(bool c, const char *message)
{
  assert(!c, message);
}

void assert_false(bool c)
{
  assert_false(c, DEFAULT_MESSAGE);
}
