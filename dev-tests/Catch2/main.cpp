#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <k3/tok3n.h>
#include <iostream>

auto p = k3::tok3n::any<"123"> >> k3::tok3n::any<"abc">;

TEST_CASE("ABC", "ABCDEFG")
{
    REQUIRE(p.family == k3::tok3n::ParserFamily::Sequence);
    REQUIRE(p.parse("1a").has_value());
    REQUIRE(*p.parse("1a") == std::tuple("1", "a"));
}

int main( int argc, char* argv[] )
{
    // your setup ...

    int result = Catch::Session().run( argc, argv );

    // your clean-up...

    return result;
}
