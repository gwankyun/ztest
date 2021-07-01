module;

#ifndef USE_MODULE
#  define USE_MODULE 1
#endif

#if !USE_MODULE
#  include "ztest.hpp"
#endif

#include "macro.h"

module main;

#if USE_MODULE
  import ztest;
#endif

int main()
{
    ztest::testCase("add");
    REQUIRE(1 + 1 == 2);
    REQUIRE(1 + 1 == 3);
    REQUIRE(1 + 1 == 4);

    ztest::testCase("minus");
    REQUIRE(1 - 1 == 0);
    REQUIRE(2 - 1 == 1);

    return 0;
}
