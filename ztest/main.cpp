import ztest;
import std.core;

#ifndef STRINGIFY_IMPL
#  define STRINGIFY_IMPL(x) #x
#endif

#ifndef STRINGIFY
#  define STRINGIFY(x) STRINGIFY_IMPL(x)
#endif

#ifndef REQUIRE
#  define REQUIRE(_case, _expr) _case.require(STRINGIFY(_expr), _expr)
#endif

#ifndef EXPR
#  define EXPR(_expr) std::make_pair(STRINGIFY(_expr), _expr)
#endif

int main()
{
    ztest::Test& test = ztest::get();

    test.addCase("plus");
    test.require(EXPR(1 + 1 == 2));
    test.require(EXPR(1 + 1 == 3));

    test.addCase("minus");
    test.require(EXPR(1 - 1 == 0));
    test.require(EXPR(2 - 1 == 1));

    test.addCase("multiply");
    test.require(EXPR(2 * 3 == 6));

    test.addCase("divide");
    test.require(EXPR(6 / 3 == 2));

    return 0;
}
