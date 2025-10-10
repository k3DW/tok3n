// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

using L = all_of_parser<TT("literal")>;

FIXTURE("all_of_parser");

TEST("all_of_parser", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(L, value_type);
    ASSERT_IS_PARSER(L, char, all_of_family, output_span<char>);
    ASSERT_IS_PARSER(L, wchar_t, all_of_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(L, int, all_of_family, output_span<int>);
}

TEST("all_of_parser", "Parse 'literal'")
{
    ASSERT_PARSE_SUCCESS(L, "literal", "literal", "");
    ASSERT_PARSE_SUCCESS(L, "literally", "literal", "ly");
    ASSERT_PARSE_FAILURE(L, "litera");
    ASSERT_PARSE_FAILURE(L, " literal");
    ASSERT_PARSE_FAILURE(L, "LITERAL");
    ASSERT_PARSE_FAILURE(L, "LITERALLY");

    ASSERT_PARSE_SUCCESS(L, L"literal", L"literal", L"");
    ASSERT_PARSE_SUCCESS(L, L"literally", L"literal", L"ly");
    ASSERT_PARSE_FAILURE(L, L"litera");
    ASSERT_PARSE_FAILURE(L, L" literal");
    ASSERT_PARSE_FAILURE(L, L"LITERAL");
    ASSERT_PARSE_FAILURE(L, L"LITERALLY");

    ASSERT_PARSE_SUCCESS(L, e<int>("literal"), e<int>("literal"), e<int>());
    ASSERT_PARSE_SUCCESS(L, e<int>("literally"), e<int>("literal"), e<int>("ly"));
    ASSERT_PARSE_FAILURE(L, e<int>("litera"));
    ASSERT_PARSE_FAILURE(L, e<int>(" literal"));
    ASSERT_PARSE_FAILURE(L, e<int>("LITERAL"));
    ASSERT_PARSE_FAILURE(L, e<int>("LITERALLY"));
}



TEST("all_of_parser", "Parse empty")
{
    ASSERT_BASIC_PARSER_CONSTRUCTIBLE(all_of_parser, TT(""));

    ASSERT_PARSE_SUCCESS(all_of_parser<"">, "anything", "", "anything");
    ASSERT_PARSE_SUCCESS(all_of_parser<"">, "", "", "");

    ASSERT_PARSE_SUCCESS(all_of_parser<L"">, L"anything", L"", L"anything");
    ASSERT_PARSE_SUCCESS(all_of_parser<L"">, L"", L"", L"");

    ASSERT_PARSE_SUCCESS(all_of_parser<"">, e<int>("anything"), e<int>(), e<int>("anything"));
    ASSERT_PARSE_SUCCESS(all_of_parser<"">, e<int>(), e<int>(), e<int>());
}
