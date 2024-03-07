#include <doctest/doctest.h>
#include <k3/tok3n.h>
#include <iostream>

auto p = k3::tok3n::any<"123"> >> k3::tok3n::any<"abc">;

TEST_CASE("ABC")
{
    CHECK(p.family == k3::tok3n::ParserFamily::Sequence);
    CHECK(p.parse("1a").has_value());
    CHECK(*p.parse("1a") == std::tuple("1", "a"));
}

// https://github.com/doctest/doctest/blob/master/doc/markdown/commandline.md
int main(int argc, const char** argv)
{
    doctest::Context context(argc, argv);
    int test_result = context.run(); // run queries, or run tests unless --no-run

    return test_result;
}
