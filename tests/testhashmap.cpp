#include "testframework.h"
#include "../util/hashmap.h"

void test_HashMap()
{
  test_category("HashMap");

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
