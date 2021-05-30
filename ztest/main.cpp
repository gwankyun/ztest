import ztest;
import std.core;

#ifndef STRINGIFY_IMPL
#  define STRINGIFY_IMPL(x) #x
#endif

#ifndef STRINGIFY
#  define STRINGIFY(x) STRINGIFY_IMPL(x)
#endif

#ifndef EXPR
#  define EXPR(_expr) std::make_pair(STRINGIFY(_expr), _expr)
#endif

#ifndef TEST_CASE
#  define TEST_CASE(...) ztest::get().addCase(##__VA_ARGS__)
#endif

#ifndef REQUIRE
#  define REQUIRE(...) ztest::get().require(EXPR(##__VA_ARGS__))
#endif

int main()
{
    ztest::Test& test = ztest::get();

    TEST_CASE("plus");
    REQUIRE(1 + 1 == 2);
    REQUIRE(1 + 1 == 3);

    TEST_CASE("minus");
    REQUIRE(1 - 1 == 0);
    REQUIRE(2 - 1 == 1);

    TEST_CASE("multiply");
    REQUIRE(2 * 3 == 6);

    TEST_CASE("divide");
    REQUIRE(6 / 3 == 2);

    return 0;
}
