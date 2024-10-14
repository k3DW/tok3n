// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("join_exactly_basic");

using Joi_Exa_OC = join_parser<exactly_parser<any_of_parser<TT("123")>, index_c<2>>>;
using Joi_Exa_NC = join_parser<exactly_parser<none_of_parser<TT("123")>, index_c<2>>>;
using Joi_Exa_L  = join_parser<exactly_parser<all_of_parser<TT("123")>, index_c<2>>>;

TEST("join_exactly_basic", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Joi_Exa_OC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Exa_NC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Exa_L, value_type);

    ASSERT_IS_PARSER(Joi_Exa_OC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_Exa_NC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_Exa_L, char, join_family, output_span<char>);

    ASSERT_IS_PARSER(Joi_Exa_OC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Exa_NC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Exa_L, wchar_t, join_family, output_span<wchar_t>);

    ASSERT_IS_PARSER(Joi_Exa_OC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_Exa_NC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_Exa_L, int, join_family, output_span<int>);
}

TEST("join_exactly_basic", "exactly_parser<any_of_parser, 2>")
{
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "12321321", "12", "321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "1232 1321", "12", "32 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "12341321", "12", "341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "1012341321");

    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, L"12321321", L"12", L"321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, L"1232 1321", L"12", L"32 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, L"12341321", L"12", L"341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"1012341321");

    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, e<int>("12321321"), e<int>("12"), e<int>("321321"));
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, e<int>("1232 1321"), e<int>("12"), e<int>("32 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, e<int>("12341321"), e<int>("12"), e<int>("341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>("012341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>("0012341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, e<int>("1012341321"));
}

TEST("join_exactly_basic", "exactly_parser<none_of_parser, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "012341321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_NC, "0012341321", "00", "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L" 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"012341321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_NC, L"0012341321", L"00", L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"1012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("1232 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>(" 12321321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("012341321"));
    ASSERT_PARSE_SUCCESS(Joi_Exa_NC, e<int>("0012341321"), e<int>("00"), e<int>("12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, e<int>("1012341321"));
}

TEST("join_exactly_basic", "exactly_parser<all_of_parser, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L" 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"012341321");

    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Exa_L, e<int>("12312321321"), e<int>("123123"), e<int>("21321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("1232 1321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>(" 12321321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("12341321"));
    ASSERT_PARSE_FAILURE(Joi_Exa_L, e<int>("012341321"));
}
