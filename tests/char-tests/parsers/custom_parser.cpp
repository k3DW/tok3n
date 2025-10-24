// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("custom_parser");

TEST("custom_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Cus1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Cus2> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Cus1> | has_family<custom_family>);
    EXPECT_THAT(the_parser<Cus2> | has_family<custom_family>);

    ASSERT_IS_PARSER(Cus1, char, custom_family, std::size_t);
    ASSERT_IS_PARSER(Cus2, char, custom_family, std::size_t);

    ASSERT_IS_PARSER(Cus1, wchar_t, custom_family, std::size_t);
    ASSERT_IS_PARSER(Cus2, wchar_t, custom_family, std::size_t);

    ASSERT_IS_PARSER(Cus1, int, custom_family, std::size_t);
    ASSERT_IS_PARSER(Cus2, int, custom_family, std::size_t);
}

TEST("custom_parser", "Parse Cus1")
{
    ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc??", 36, "");
    ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc", 12, "");
    ASSERT_PARSE_SUCCESS(Cus1, "abcabcabcabc ??", 12, " ??");
    ASSERT_PARSE_SUCCESS(Cus1, "abc", 3, "");
    ASSERT_PARSE_FAILURE(Cus1, " abc");
    ASSERT_PARSE_FAILURE(Cus1, "");

    ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc??", 36, L"");
    ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc", 12, L"");
    ASSERT_PARSE_SUCCESS(Cus1, L"abcabcabcabc ??", 12, L" ??");
    ASSERT_PARSE_SUCCESS(Cus1, L"abc", 3, L"");
    ASSERT_PARSE_FAILURE(Cus1, L" abc");
    ASSERT_PARSE_FAILURE(Cus1, L"");

    ASSERT_PARSE_SUCCESS(Cus1, e<int>("abcabcabcabc??"), 36, e<int>(""));
    ASSERT_PARSE_SUCCESS(Cus1, e<int>("abcabcabcabc"), 12, e<int>(""));
    ASSERT_PARSE_SUCCESS(Cus1, e<int>("abcabcabcabc ??"), 12, e<int>(" ??"));
    ASSERT_PARSE_SUCCESS(Cus1, e<int>("abc"), 3, e<int>(""));
    ASSERT_PARSE_FAILURE(Cus1, e<int>(" abc"));
    ASSERT_PARSE_FAILURE(Cus1, e<int>(""));
}

TEST("custom_parser", "Parse Cus2")
{
    ASSERT_PARSE_SUCCESS(Cus2, "abc", 0, "bc");
    ASSERT_PARSE_SUCCESS(Cus2, "bca", 0, "ca");
    ASSERT_PARSE_SUCCESS(Cus2, "cab", 0, "ab");
    ASSERT_PARSE_FAILURE(Cus2, "xyz");
    ASSERT_PARSE_FAILURE(Cus2, "");

    ASSERT_PARSE_SUCCESS(Cus2, L"abc", 0, L"bc");
    ASSERT_PARSE_SUCCESS(Cus2, L"bca", 0, L"ca");
    ASSERT_PARSE_SUCCESS(Cus2, L"cab", 0, L"ab");
    ASSERT_PARSE_FAILURE(Cus2, L"xyz");
    ASSERT_PARSE_FAILURE(Cus2, L"");

    ASSERT_PARSE_SUCCESS(Cus2, e<int>("abc"), 0, e<int>("bc"));
    ASSERT_PARSE_SUCCESS(Cus2, e<int>("bca"), 0, e<int>("ca"));
    ASSERT_PARSE_SUCCESS(Cus2, e<int>("cab"), 0, e<int>("ab"));
    ASSERT_PARSE_FAILURE(Cus2, e<int>("xyz"));
    ASSERT_PARSE_FAILURE(Cus2, e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
