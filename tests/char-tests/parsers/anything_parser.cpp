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
    ASSERT_PARSE_SUCCESS(Ant1, "ab", "a", "b");
    ASSERT_PARSE_SUCCESS(Ant1, "ba", "b", "a");
    ASSERT_PARSE_SUCCESS(Ant1, "abc", "a", "bc");
    ASSERT_PARSE_SUCCESS(Ant1, "Ab", "A", "b");
    ASSERT_PARSE_SUCCESS(Ant1, "Abc", "A", "bc");
    ASSERT_PARSE_SUCCESS(Ant1, " abc", " ", "abc");
    ASSERT_PARSE_FAILURE(Ant1, "");

    ASSERT_PARSE_SUCCESS(Ant1, L"ab", L"a", L"b");
    ASSERT_PARSE_SUCCESS(Ant1, L"ba", L"b", L"a");
    ASSERT_PARSE_SUCCESS(Ant1, L"abc", L"a", L"bc");
    ASSERT_PARSE_SUCCESS(Ant1, L"Ab", L"A", L"b");
    ASSERT_PARSE_SUCCESS(Ant1, L"Abc", L"A", L"bc");
    ASSERT_PARSE_SUCCESS(Ant1, L" abc", L" ", L"abc");
    ASSERT_PARSE_FAILURE(Ant1, L"");

    ASSERT_PARSE_SUCCESS(Ant1, e<int>("ab"), e<int>("a"), e<int>("b"));
    ASSERT_PARSE_SUCCESS(Ant1, e<int>("ba"), e<int>("b"), e<int>("a"));
    ASSERT_PARSE_SUCCESS(Ant1, e<int>("abc"), e<int>("a"), e<int>("bc"));
    ASSERT_PARSE_SUCCESS(Ant1, e<int>("Ab"), e<int>("A"), e<int>("b"));
    ASSERT_PARSE_SUCCESS(Ant1, e<int>("Abc"), e<int>("A"), e<int>("bc"));
    ASSERT_PARSE_SUCCESS(Ant1, e<int>(" abc"), e<int>(" "), e<int>("abc"));
    ASSERT_PARSE_FAILURE(Ant1, e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
