#include "testframework.h"
#include "../util/deque.h"

void test_Deque()
{
  test_category("Deque");

  Deque<int> d;
  for (int i = 0; i < 5; ++i)
  {
    d.push_front(-i - 1);
    d.push_back(i);
  }

  assert(d[0] == -5, "zero");
  assert(d.front() == -5, "front");
  assert(d.back() == 4, "back");
  assert(d[3] == -2, "middle");
}
