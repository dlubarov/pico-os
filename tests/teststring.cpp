#include "testframework.h"
#include "../util/string.h"

void test_String()
{
  test_category("String");

  String a("a"),
         b("b"),
         aa("aa"),
         bb("bb"),
         foo("foo"),
         bar("bar"),
         baz("baz"),
         empty;

  assert(foo == foo, "==");
  assert(bar == bar, "==");
  assert(baz == baz, "==");
  assert(empty == empty, "==");

  assert_false(foo == bar);
  assert_false(baz == empty);

  assert(foo != bar, "!=");
  assert(bar != baz, "!=");
  assert(baz != empty, "!=");
  assert(empty != foo, "!=");

  assert_false(foo != foo);
  assert_false(empty != empty);

  assert(a + a == aa, "+");
  assert(b + b == bb, "+");
  assert(a + a == a + a, "+");
  assert(b + b == b + b, "+");
  assert(a + b == a + b, "+");
  assert(a + b != b + a, "+");
}
