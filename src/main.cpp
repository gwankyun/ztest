module;

#ifndef USE_MODULE
#  define USE_MODULE 1
#endif

#if USE_MODULE
#  include "ztest/macro.h"
#else
#  include "ztest/ztest.hpp"
#endif

module main;

#if USE_MODULE
  import ztest;
#endif

int main()
{
    TEST_CASE("add", "ztest")
    {
        REQUIRE(1 + 1 == 2);
        REQUIRE(1 + 1 == 3);
        REQUIRE(1 + 1 == 4);
    }

    TEST_CASE("minus", "ztest")
    {
        REQUIRE(1 - 1 == 0);
        REQUIRE(2 - 1 == 1);
    }

    return 0;
}
