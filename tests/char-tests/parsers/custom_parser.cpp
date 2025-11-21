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

    EXPECT_THAT(the_parser<Cus1> | is_parser_for<char>.with_result<std::size_t>);
    EXPECT_THAT(the_parser<Cus2> | is_parser_for<char>.with_result<std::size_t>);

    EXPECT_THAT(the_parser<Cus1> | is_parser_for<wchar_t>.with_result<std::size_t>);
    EXPECT_THAT(the_parser<Cus2> | is_parser_for<wchar_t>.with_result<std::size_t>);

    EXPECT_THAT(the_parser<Cus1> | is_parser_for<int>.with_result<std::size_t>);
    EXPECT_THAT(the_parser<Cus2> | is_parser_for<int>.with_result<std::size_t>);
}

TEST("custom_parser", "Parse Cus1")
{
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING("abcabcabcabc??", 36, ""));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING("abcabcabcabc", 12, ""));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING("abcabcabcabc ??", 12, " ??"));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING("abc", 3, ""));
    ASSERT_PARSE_FAILURE(Cus1, " abc");
    ASSERT_PARSE_FAILURE(Cus1, "");

    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(L"abcabcabcabc??", 36, L""));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(L"abcabcabcabc", 12, L""));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(L"abcabcabcabc ??", 12, L" ??"));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(L"abc", 3, L""));
    ASSERT_PARSE_FAILURE(Cus1, L" abc");
    ASSERT_PARSE_FAILURE(Cus1, L"");

    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(e<int>("abcabcabcabc??"), 36, e<int>("")));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(e<int>("abcabcabcabc"), 12, e<int>("")));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(e<int>("abcabcabcabc ??"), 12, e<int>(" ??")));
    EXPECT_THAT(the_parser<Cus1> | SUCCEEDS_PARSING(e<int>("abc"), 3, e<int>("")));
    ASSERT_PARSE_FAILURE(Cus1, e<int>(" abc"));
    ASSERT_PARSE_FAILURE(Cus1, e<int>(""));
}

TEST("custom_parser", "Parse Cus2")
{
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING("abc", 0, "bc"));
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING("bca", 0, "ca"));
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING("cab", 0, "ab"));
    ASSERT_PARSE_FAILURE(Cus2, "xyz");
    ASSERT_PARSE_FAILURE(Cus2, "");

    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING(L"abc", 0, L"bc"));
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING(L"bca", 0, L"ca"));
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING(L"cab", 0, L"ab"));
    ASSERT_PARSE_FAILURE(Cus2, L"xyz");
    ASSERT_PARSE_FAILURE(Cus2, L"");

    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING(e<int>("abc"), 0, e<int>("bc")));
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING(e<int>("bca"), 0, e<int>("ca")));
    EXPECT_THAT(the_parser<Cus2> | SUCCEEDS_PARSING(e<int>("cab"), 0, e<int>("ab")));
    ASSERT_PARSE_FAILURE(Cus2, e<int>("xyz"));
    ASSERT_PARSE_FAILURE(Cus2, e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
