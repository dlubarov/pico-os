#include "testframework.h"
#include "../util/vector.h"

void test_Vector()
{
  test_category("Vector");

  Vector<int> v1;
  for (int i = 0; i < 50; ++i)
    v1.push_back(i);

  for (int i = 49; i >= 0; --i)
  {
    int n1 = v1.back();
    int n2 = v1[v1.len() - 1];
    int n3 = v1.pop_back();

    assert(i == n1, "back");
    assert(i == n2, "subscript");
    assert(i == n3, "pop_back");
  }
}
