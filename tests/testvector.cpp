#include "../util/vector.h"
#include "../common.h"

void test_Vector()
{
  Vector<int> v1;
  for (int i = 0; i < 50; ++i)
    v1.push_back(i);
  for (int i = 49; i >= 0; --i)
  {
    int n1 = v1.back();
    int n2 = v1[v1.len() - 1];
    int n3 = v1.pop_back();
    ASSERT(i == n1, "n1");
    ASSERT(i == n2, "n2");
    ASSERT(i == n3, "n3");
  }
}
