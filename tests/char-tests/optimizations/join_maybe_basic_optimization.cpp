// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("join_maybe_basic");

using Joi_May_OC = join_parser<maybe_parser<any_of_parser<TT("123")>>>;
using Joi_May_NC = join_parser<maybe_parser<none_of_parser<TT("123")>>>;
using Joi_May_L  = join_parser<maybe_parser<all_of_parser<TT("123")>>>;

TEST("join_maybe_basic", "Requirements")
{
    EXPECT_THAT(the_parser<Joi_May_OC> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi_May_NC> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi_May_L> | has_value_type<value_type>);

    ASSERT_IS_PARSER(Joi_May_OC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_May_NC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_May_L, char, join_family, output_span<char>);

    ASSERT_IS_PARSER(Joi_May_OC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_May_NC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_May_L, wchar_t, join_family, output_span<wchar_t>);

    ASSERT_IS_PARSER(Joi_May_OC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_May_NC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_May_L, int, join_family, output_span<int>);
}

TEST("join_maybe_basic", "maybe_parser<any_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12321321", "1", "2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "1232 1321", "1", "232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12341321", "1", "2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "012341321", "", "012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"12321321", L"1", L"2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"1232 1321", L"1", L"232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"12341321", L"1", L"2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"012341321", L"", L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("12321321"), e<int>("1"), e<int>("2321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("1232 1321"), e<int>("1"), e<int>("232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>(" 12321321"), e<int>(""), e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("12341321"), e<int>("1"), e<int>("2341321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("012341321"), e<int>(""), e<int>("012341321"));

    using P = complete_parser<Joi_May_OC>; // Wrap the parser to test its nestability
    ASSERT_PARSE_SUCCESS(P, "1", "1", "");
    ASSERT_PARSE_SUCCESS(P, L"1", L"1", L"");
    ASSERT_PARSE_SUCCESS(P, e<int>("1"), e<int>("1"), e<int>(""));
}

TEST("join_maybe_basic", "maybe_parser<none_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "012341321", "0", "12341321");

    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"12321321", L"", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"1232 1321", L"", L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"12341321", L"", L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"012341321", L"0", L"12341321");

    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("12321321"), e<int>(""), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("1232 1321"), e<int>(""), e<int>("1232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>(" 12321321"), e<int>(" "), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("12341321"), e<int>(""), e<int>("12341321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("012341321"), e<int>("0"), e<int>("12341321"));

    using P = complete_parser<Joi_May_NC>; // Wrap the parser to test its nestability
    ASSERT_PARSE_SUCCESS(P, "4", "4", "");
    ASSERT_PARSE_SUCCESS(P, L"4", L"4", L"");
    ASSERT_PARSE_SUCCESS(P, e<int>("4"), e<int>("4"), e<int>(""));
}

TEST("join_maybe_basic", "maybe_parser<all_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12312321321", "123", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "012341321", "", "012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12312321321", L"123", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"012341321", L"", L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("12321321"), e<int>("123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("12312321321"), e<int>("123"), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("1232 1321"), e<int>("123"), e<int>("2 1321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>(" 12321321"), e<int>(""), e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("012341321"), e<int>(""), e<int>("012341321"));

    using P = complete_parser<Joi_May_L>; // Wrap the parser to test its nestability
    ASSERT_PARSE_SUCCESS(P, "123", "123", "");
    ASSERT_PARSE_SUCCESS(P, L"123", L"123", L"");
    ASSERT_PARSE_SUCCESS(P, e<int>("123"), e<int>("123"), e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
