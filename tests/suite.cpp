#include "suite.h"
#include "../common.h"

void test_all()
{
  test_CircularBuffer();
  kputs("CircularBuffer passed");

  test_Deque();
  kputs("Deque passed");

  test_Vector();
  kputs("Vector passed");

  test_HashMap();
  kputs("HashMap passed");

  kprintf("all tests passed :-)\n");
}
