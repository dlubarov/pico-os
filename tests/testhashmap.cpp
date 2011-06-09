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

  assert(M["one"] == 1, "map");
  assert(M["two"] == 2, "map");
  assert(M["three"] == 3, "map");
  assert(M["four"] == 4, "map");
  assert(M["five"] == 5, "map");
  assert(M["six"] == 6, "map");
  assert(M["seven"] == 7, "map");
  assert(M["eight"] == 8, "map");
  assert(M["nine"] == 9, "map");
  assert(M["ten"] == 10, "map");
}
