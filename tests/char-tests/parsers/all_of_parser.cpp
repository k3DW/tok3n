// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using L = all_of_parser<TT("literal")>;

FIXTURE("all_of_parser");

TEST("all_of_parser", "Requirements")
{
    EXPECT_THAT(the_parser<L> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<L> | has_family<all_of_family>);
    EXPECT_THAT(the_parser<L> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<L> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<L> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("all_of_parser", "Parse 'literal'")
{
    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING("literal", "literal", ""));
    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING("literally", "literal", "ly"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING("litera"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(" literal"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING("LITERAL"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING("LITERALLY"));

    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING(L"literal", L"literal", L""));
    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING(L"literally", L"literal", L"ly"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(L"litera"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(L" literal"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(L"LITERAL"));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(L"LITERALLY"));

    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING(e<int>("literal"), e<int>("literal"), e<int>()));
    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING(e<int>("literally"), e<int>("literal"), e<int>("ly")));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(e<int>("litera")));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(e<int>(" literal")));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(e<int>("LITERAL")));
    EXPECT_THAT(the_parser<L> | FAILS_PARSING(e<int>("LITERALLY")));
}



TEST("all_of_parser", "Parse empty")
{
    EXPECT_THAT(the_basic_parser_family<all_of_parser>.is_valid_with<TT("")>);

    EXPECT_THAT(the_parser<all_of_parser<"">> | SUCCEEDS_PARSING("anything", "", "anything"));
    EXPECT_THAT(the_parser<all_of_parser<"">> | SUCCEEDS_PARSING("", "", ""));

    EXPECT_THAT(the_parser<all_of_parser<L"">> | SUCCEEDS_PARSING(L"anything", L"", L"anything"));
    EXPECT_THAT(the_parser<all_of_parser<L"">> | SUCCEEDS_PARSING(L"", L"", L""));

    EXPECT_THAT(the_parser<all_of_parser<"">> | SUCCEEDS_PARSING(e<int>("anything"), e<int>(), e<int>("anything")));
    EXPECT_THAT(the_parser<all_of_parser<"">> | SUCCEEDS_PARSING(e<int>(), e<int>(), e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
