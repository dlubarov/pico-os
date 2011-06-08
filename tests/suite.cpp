#include "../common.h"

void test_CircularBuffer();
void test_HashMap();

void test_all()
{
  test_CircularBuffer();
  test_HashMap();
  kprintf("all tests passed\n");
}
