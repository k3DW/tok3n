#include <doctest/doctest.h>
#include <k3/tok3n.h>
#include <iostream>
#include <format>

using namespace k3::tok3n::operators;

auto digit = "0123456789"_any_of;
auto year = exactly<4>(digit) % join;
auto month = exactly<2>(digit) % join;
auto day = digit % exactly<2> % join;

auto parser = year >> "-"_ign >> month >> "-"_ign >> day;

#if 0
TEST_CASE("ISO8601")
{
    std::string_view input = "2024-01-01";
    auto result = parser.parse(input);

    REQUIRE(result.has_value());
    CHECK(*result == std::tuple("2024", "01", "01"));
}
#else
TEST_CASE("ISO8601")
{
    std::string_view input = "bad";
    auto result = parser.parse(input);

    INFO(std::format("Input could not be parsed.\nInput = \"{}\"\n"
        "Parser = {}", input, k3::tok3n::pretty(parser).view()));

    REQUIRE(result.has_value());
    CHECK(*result == std::tuple("2024", "01", "01"));
}
#endif

// https://github.com/doctest/doctest/blob/master/doc/markdown/commandline.md
int main(int argc, const char** argv)
{
    doctest::Context context(argc, argv);
    int test_result = context.run(); // run queries, or run tests unless --no-run

    return test_result;
}
