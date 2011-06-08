#include "../util/circularbuffer.h"

void test_CircularBuffer()
{
  for (int n = 0; n < 100; ++n)
  {
    CircularBuffer<int> cb(n*2);
    for (int i = 0; i < n; ++i)
    {
      cb.push_front(-i - 1);
      cb.push_back(i);
    }
    for (int i = 0; i < n*2; ++i)
    {
      int val = cb.pop_front();
      ASSERT(val == i - n, "cbuf failed 2");
    }
  }

  CircularBuffer<int> b(6);
  b[0] = 10; b[1] = 20; b[2] = 30;
  b[3] = 40; b[4] = 50; b[5] = 60;
  for (int i = 0; i < 6; ++i)
    ASSERT(b[i] == (i+1)*10, "cbuf failed 2");

  b[2] = 100;
  b.front() = 42; b.back() = 64;
  ASSERT(b[0] == 42, "cbuf front");
  ASSERT(b[5] == 64, "cbuf back");
  ASSERT(b[2] == 100, "cbuf sub");
}
