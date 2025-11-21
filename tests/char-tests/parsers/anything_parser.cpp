// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("anything_parser");

TEST("anything_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Ant1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Ant1> | has_family<anything_family>);

    EXPECT_THAT(the_parser<Ant1> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Ant1> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Ant1> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("anything_parser", "Parse")
{
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING("ab", "a", "b"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING("ba", "b", "a"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING("abc", "a", "bc"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING("Ab", "A", "b"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING("Abc", "A", "bc"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(" abc", " ", "abc"));
    ASSERT_PARSE_FAILURE(Ant1, "");

    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(L"ab", L"a", L"b"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(L"ba", L"b", L"a"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(L"abc", L"a", L"bc"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(L"Ab", L"A", L"b"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(L"Abc", L"A", L"bc"));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(L" abc", L" ", L"abc"));
    ASSERT_PARSE_FAILURE(Ant1, L"");

    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e<int>("ab"), e<int>("a"), e<int>("b")));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e<int>("ba"), e<int>("b"), e<int>("a")));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e<int>("abc"), e<int>("a"), e<int>("bc")));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e<int>("Ab"), e<int>("A"), e<int>("b")));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e<int>("Abc"), e<int>("A"), e<int>("bc")));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e<int>(" abc"), e<int>(" "), e<int>("abc")));
    ASSERT_PARSE_FAILURE(Ant1, e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
