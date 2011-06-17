#include "testframework.h"
#include "../util/hashmap.h"

void test_StringHashMap()
{
  test_category("StringHashMap");

  StringHashMap<int> M;
  M["eight"] = 8;
  M["five"] = 5;
  M["one"] = 1;
  M["nine"] = 9;
  M["two"] = 2;
  M["four"] = 4;
  M["ten"] = 10;
  M["six"] = 6;
  M["three"] = 3;
  M["seven"] = 7;

  assert(M.contains("three"));
  assert(M.contains("five"));
  assert(M.contains("ten"));

  assert_false(M.contains(""));
  assert_false(M.contains("twenty"));
  assert_false(M.contains("!@#%^"));

  assert(M["one"]   == 1,  "lookup");
  assert(M["two"]   == 2,  "lookup");
  assert(M["three"] == 3,  "lookup");
  assert(M["four"]  == 4,  "lookup");
  assert(M["five"]  == 5,  "lookup");
  assert(M["six"]   == 6,  "lookup");
  assert(M["seven"] == 7,  "lookup");
  assert(M["eight"] == 8,  "lookup");
  assert(M["nine"]  == 9,  "lookup");
  assert(M["ten"]   == 10, "lookup");

  M["foo"] = 50; M["foo"] = 80;
  M["foo"] = M["foo"] = 42;
  M["foo"] = M["foo"] = M["foo"] = M["foo"];

  assert(M["foo"] == 42, "foo");
}

void test_UIntHashMap()
{
  test_category("UIntHashMap");

  UIntHashMap<int> M;
  int nums[] = {0, 1, 2, 3, 4, 5, 7, 21, 29, 100, -1, -100, -29, 1000, -1000, 9999};
  unsigned int len = sizeof(nums) / sizeof(nums[0]);
  for (unsigned int i = 0; i < len; ++i)
  {
    int n = nums[i];
    M[n] = 1234567;
    M[n] = 3 * n - 1;
    M[n] = M[n] = M[n];
  }
  for (unsigned int i = 0; i < len; ++i)
  {
    int n = nums[i];
    assert(M[n] == 3 * n - 1, "3n-1");
  }
}

void test_HashMap()
{
  test_StringHashMap();
  test_UIntHashMap();
}
