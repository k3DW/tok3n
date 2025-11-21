// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("join_one_or_more_basic");

using Joi_Oom_OC = join_parser<one_or_more_parser<any_of_parser<TT("123")>>>;
using Joi_Oom_NC = join_parser<one_or_more_parser<none_of_parser<TT("123")>>>;
using Joi_Oom_L  = join_parser<one_or_more_parser<all_of_parser<TT("123")>>>;

TEST("join_one_or_more_basic", "Requirements")
{
    EXPECT_THAT(the_parser<Joi_Oom_OC> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi_Oom_NC> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Joi_Oom_L> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Joi_Oom_OC> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi_Oom_NC> | has_family<join_family>);
    EXPECT_THAT(the_parser<Joi_Oom_L> | has_family<join_family>);

    EXPECT_THAT(the_parser<Joi_Oom_OC> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi_Oom_NC> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<Joi_Oom_L> | is_parser_for<char>.with_result<output_span<char>>);

    EXPECT_THAT(the_parser<Joi_Oom_OC> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi_Oom_NC> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<Joi_Oom_L> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);

    EXPECT_THAT(the_parser<Joi_Oom_OC> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi_Oom_NC> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<Joi_Oom_L> | is_parser_for<int>.with_result<output_span<int>>);
}

TEST("join_one_or_more_basic", "one_or_more_parser<any_of_parser>")
{
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING("12321321", "12321321", ""));
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING("1232 1321", "1232", " 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, " 12321321");
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING("12341321", "123", "41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, "012341321");

    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING(L"12321321", L"12321321", L""));
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING(L"1232 1321", L"1232", L" 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L" 12321321");
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING(L"12341321", L"123", L"41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L"012341321");

    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>("12321321"), e<int>("")));
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING(e<int>("1232 1321"), e<int>("1232"), e<int>(" 1321")));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, e<int>(" 12321321"));
    EXPECT_THAT(the_parser<Joi_Oom_OC> | SUCCEEDS_PARSING(e<int>("12341321"), e<int>("123"), e<int>("41321")));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, e<int>("012341321"));

    using P = complete_parser<Joi_Oom_OC>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("12321321", "12321321", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"12321321", L"12321321", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>("12321321"), e<int>("")));
}

TEST("join_one_or_more_basic", "one_or_more_parser<none_of_parser>")
{
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "1232 1321");
    EXPECT_THAT(the_parser<Joi_Oom_NC> | SUCCEEDS_PARSING(" 12321321", " ", "12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12341321");
    EXPECT_THAT(the_parser<Joi_Oom_NC> | SUCCEEDS_PARSING("012341321", "0", "12341321"));

    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"1232 1321");
    EXPECT_THAT(the_parser<Joi_Oom_NC> | SUCCEEDS_PARSING(L" 12321321", L" ", L"12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12341321");
    EXPECT_THAT(the_parser<Joi_Oom_NC> | SUCCEEDS_PARSING(L"012341321", L"0", L"12341321"));

    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("1232 1321"));
    EXPECT_THAT(the_parser<Joi_Oom_NC> | SUCCEEDS_PARSING(e<int>(" 12321321"), e<int>(" "), e<int>("12321321")));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("12341321"));
    EXPECT_THAT(the_parser<Joi_Oom_NC> | SUCCEEDS_PARSING(e<int>("012341321"), e<int>("0"), e<int>("12341321")));

    using P = complete_parser<Joi_Oom_NC>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("45654654", "45654654", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"45654654", L"45654654", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("45654654"), e<int>("45654654"), e<int>("")));
}

TEST("join_one_or_more_basic", "one_or_more_parser<all_of_parser>")
{
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING("12321321", "123", "21321"));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING("12312321321", "123123", "21321"));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING("1232 1321", "123", "2 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, " 12321321");
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING("12341321", "123", "41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, "012341321");

    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(L"12321321", L"123", L"21321"));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(L"12312321321", L"123123", L"21321"));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(L"1232 1321", L"123", L"2 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L" 12321321");
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(L"12341321", L"123", L"41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L"012341321");

    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(e<int>("12321321"), e<int>("123"), e<int>("21321")));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(e<int>("12312321321"), e<int>("123123"), e<int>("21321")));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(e<int>("1232 1321"), e<int>("123"), e<int>("2 1321")));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, e<int>(" 12321321"));
    EXPECT_THAT(the_parser<Joi_Oom_L> | SUCCEEDS_PARSING(e<int>("12341321"), e<int>("123"), e<int>("41321")));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, e<int>("012341321"));

    using P = complete_parser<Joi_Oom_L>; // Wrap the parser to test its nestability
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("123123123", "123123123", ""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"123123123", L"123123123", L""));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("123123123"), e<int>("123123123"), e<int>("")));
}

} // namespace
} // namespace k3::tok3n::tests
