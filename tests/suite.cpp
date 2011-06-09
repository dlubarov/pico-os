#include "testframework.h"
#include "suite.h"
#include "../common.h"

void test_all()
{
  kputs("running all tests...");

  test_String();
  test_CircularBuffer();
  test_Deque();
  test_Vector();
  test_HashMap();

  if (STOP_ON_FAILURE)
    kputs("all tests passed :-)");
}
