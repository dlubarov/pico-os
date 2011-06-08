#include "../util/deque.h"

void test_Deque()
{
  Deque<int> d;
  for (int i = 0; i < 5; ++i)
  {
    d.push_front(-i - 1);
    d.push_back(i);
  }
  ASSERT(d[0] == -5, "test failure: deque zero");
  ASSERT(d.front() == -5, "test failure: deque front");
  ASSERT(d.back() == 4, "test failure: deque back");
  ASSERT(d[3] == -2, "test failure: deque middle");
}
