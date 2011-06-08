#include "../util/hashmap.h"

void test_HashMap()
{
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

  ASSERT(M["one"] == 1, "map");
  ASSERT(M["two"] == 2, "map");
  ASSERT(M["three"] == 3, "map");
  ASSERT(M["four"] == 4, "map");
  ASSERT(M["five"] == 5, "map");
  ASSERT(M["six"] == 6, "map");
  ASSERT(M["seven"] == 7, "map");
  ASSERT(M["eight"] == 8, "map");
  ASSERT(M["nine"] == 9, "map");
  ASSERT(M["ten"] == 10, "map");
}
