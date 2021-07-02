#pragma once

#ifndef STRINGIFY_IMPL
#  define STRINGIFY_IMPL(x) #x
#endif

#ifndef STRINGIFY
#  define STRINGIFY(x) STRINGIFY_IMPL(x)
#endif

#ifndef EXPR
#  define EXPR(_expr) std::make_pair(STRINGIFY(_expr), _expr)
#endif

#ifndef REQUIRE
#  define REQUIRE(_expr) ztest::get().require(EXPR(_expr))
#endif

#ifndef TEST_CASE
#  define TEST_CASE(_name, _group) ztest::testCase(_name);
#endif
