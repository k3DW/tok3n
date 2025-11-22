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

    EXPECT_THAT(the_parser<Joi_May_OC> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi_May_NC> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi_May_L> | has_family<join_family>);

    EXPECT_THAT(the_parser<Joi_May_OC> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi_May_NC> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi_May_L> | is_parser_for<char>.with_result<output_span<char>>);

    EXPECT_THAT(the_parser<Joi_May_OC> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi_May_NC> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi_May_L> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);

    EXPECT_THAT(the_parser<Joi_May_OC> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi_May_NC> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi_May_L> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("join_maybe_basic", "maybe_parser<any_of_parser>")
{
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING("12321321", "1", "2321321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING("1232 1321", "1", "232 1321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(" 12321321", "", " 12321321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING("12341321", "1", "2341321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING("012341321", "", "012341321"));

    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(L"12321321", L"1", L"2321321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(L"1232 1321", L"1", L"232 1321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(L" 12321321", L"", L" 12321321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(L"12341321", L"1", L"2341321"));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(L"012341321", L"", L"012341321"));

    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>("1"), e<int>("2321321")));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(e<int>("1232 1321"), e<int>("1"), e<int>("232 1321")));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(e<int>(" 12321321"), e<int>(""), e<int>(" 12321321")));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(e<int>("12341321"), e<int>("1"), e<int>("2341321")));
    EXPECT_THAT(the_parser<Joi_May_OC> | SUCCEEDS_PARSING(e<int>("012341321"), e<int>(""), e<int>("012341321")));

    using P = complete_parser<Joi_May_OC>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("1", "1", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"1", L"1", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("1"), e<int>("1"), e<int>("")));
}

TEST("join_maybe_basic", "maybe_parser<none_of_parser>")
{
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING("12321321", "", "12321321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING("1232 1321", "", "1232 1321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(" 12321321", " ", "12321321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING("12341321", "", "12341321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING("012341321", "0", "12341321"));

    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(L"12321321", L"", L"12321321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(L"1232 1321", L"", L"1232 1321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(L" 12321321", L" ", L"12321321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(L"12341321", L"", L"12341321"));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(L"012341321", L"0", L"12341321"));

    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>(""), e<int>("12321321")));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(e<int>("1232 1321"), e<int>(""), e<int>("1232 1321")));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(e<int>(" 12321321"), e<int>(" "), e<int>("12321321")));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(e<int>("12341321"), e<int>(""), e<int>("12341321")));
    EXPECT_THAT(the_parser<Joi_May_NC> | SUCCEEDS_PARSING(e<int>("012341321"), e<int>("0"), e<int>("12341321")));

    using P = complete_parser<Joi_May_NC>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("4", "4", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"4", L"4", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("4"), e<int>("4"), e<int>("")));
}

TEST("join_maybe_basic", "maybe_parser<all_of_parser>")
{
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING("12321321", "123", "21321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING("12312321321", "123", "12321321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING("1232 1321", "123", "2 1321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(" 12321321", "", " 12321321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING("12341321", "123", "41321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING("012341321", "", "012341321"));

    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(L"12321321", L"123", L"21321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(L"12312321321", L"123", L"12321321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(L"1232 1321", L"123", L"2 1321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(L" 12321321", L"", L" 12321321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(L"12341321", L"123", L"41321"));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(L"012341321", L"", L"012341321"));

    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>("123"), e<int>("21321")));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(e<int>("12312321321"), e<int>("123"), e<int>("12321321")));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(e<int>("1232 1321"), e<int>("123"), e<int>("2 1321")));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(e<int>(" 12321321"), e<int>(""), e<int>(" 12321321")));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(e<int>("12341321"), e<int>("123"), e<int>("41321")));
    EXPECT_THAT(the_parser<Joi_May_L> | SUCCEEDS_PARSING(e<int>("012341321"), e<int>(""), e<int>("012341321")));

    using P = complete_parser<Joi_May_L>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("123", "123", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"123", L"123", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("123"), e<int>("123"), e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
