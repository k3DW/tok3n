// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("join_exactly_basic");

using Joi_Exa_OC = join_parser<exactly_parser<any_of_parser<TT("123")>, index_c<2>>>;
using Joi_Exa_NC = join_parser<exactly_parser<none_of_parser<TT("123")>, index_c<2>>>;
using Joi_Exa_L  = join_parser<exactly_parser<all_of_parser<TT("123")>, index_c<2>>>;

TEST("join_exactly_basic", "Requirements")
{
    EXPECT_THAT(the_parser<Joi_Exa_OC> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi_Exa_NC> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi_Exa_L> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Joi_Exa_OC> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi_Exa_NC> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi_Exa_L> | has_family<join_family>);

    EXPECT_THAT(the_parser<Joi_Exa_OC> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi_Exa_NC> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi_Exa_L> | is_parser_for<char>.with_result<output_span<char>>);

    EXPECT_THAT(the_parser<Joi_Exa_OC> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi_Exa_NC> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi_Exa_L> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);

    EXPECT_THAT(the_parser<Joi_Exa_OC> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi_Exa_NC> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi_Exa_L> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("join_exactly_basic", "exactly_parser<any_of_parser, 2>")
{
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING("12321321", "12", "321321"));
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING("1232 1321", "12", "32 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, " 12321321");
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING("12341321", "12", "341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "1012341321");

    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING(L"12321321", L"12", L"321321"));
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING(L"1232 1321", L"12", L"32 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L" 12321321");
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING(L"12341321", L"12", L"341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"1012341321");

    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>("12"), e<int>("321321")));
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING(e<int>("1232 1321"), e<int>("12"), e<int>("32 1321")));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>(" 12321321"));
    EXPECT_THAT(the_parser<Joi_Exa_OC> | SUCCEEDS_PARSING(e<int>("12341321"), e<int>("12"), e<int>("341321")));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>("012341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>("0012341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>("1012341321"));

    using P = complete_parser<Joi_Exa_OC>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("12", "12", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"12", L"12", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("12"), e<int>("12"), e<int>("")));
}

TEST("join_exactly_basic", "exactly_parser<none_of_parser, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "012341321");
    EXPECT_THAT(the_parser<Joi_Exa_NC> | SUCCEEDS_PARSING("0012341321", "00", "12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L" 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"012341321");
    EXPECT_THAT(the_parser<Joi_Exa_NC> | SUCCEEDS_PARSING(L"0012341321", L"00", L"12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"1012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("1232 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>(" 12321321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("012341321"));
    EXPECT_THAT(the_parser<Joi_Exa_NC> | SUCCEEDS_PARSING(e<int>("0012341321"), e<int>("00"), e<int>("12341321")));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("1012341321"));

    using P = complete_parser<Joi_Exa_NC>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("45", "45", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"45", L"45", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("45"), e<int>("45"), e<int>("")));
}

TEST("join_exactly_basic", "exactly_parser<all_of_parser, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12321321");
    EXPECT_THAT(the_parser<Joi_Exa_L> | SUCCEEDS_PARSING("12312321321", "123123", "21321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"12321321");
    EXPECT_THAT(the_parser<Joi_Exa_L> | SUCCEEDS_PARSING(L"12312321321", L"123123", L"21321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L" 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("12321321"));
    EXPECT_THAT(the_parser<Joi_Exa_L> | SUCCEEDS_PARSING(e<int>("12312321321"), e<int>("123123"), e<int>("21321")));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("1232 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>(" 12321321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("012341321"));

    using P = complete_parser<Joi_Exa_L>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("123123", "123123", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"123123", L"123123", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("123123"), e<int>("123123"), e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
