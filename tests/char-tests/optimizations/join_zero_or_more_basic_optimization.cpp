// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("join_zero_or_more_basic");

using Joi_Zom_OC = join_parser<zero_or_more_parser<any_of_parser<TT("123")>>>;
using Joi_Zom_NC = join_parser<zero_or_more_parser<none_of_parser<TT("123")>>>;
using Joi_Zom_L  = join_parser<zero_or_more_parser<all_of_parser<TT("123")>>>;

TEST("join_zero_or_more_basic", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Joi_Zom_OC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Zom_NC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Zom_L, value_type);

    ASSERT_IS_PARSER(Joi_Zom_OC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_Zom_NC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_Zom_L, char, join_family, output_span<char>);

    ASSERT_IS_PARSER(Joi_Zom_OC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Zom_NC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Zom_L, wchar_t, join_family, output_span<wchar_t>);

    ASSERT_IS_PARSER(Joi_Zom_OC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_Zom_NC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_Zom_L, int, join_family, output_span<int>);
}

TEST("join_zero_or_more_basic", "zero_or_more_parser<any_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "012341321", "", "012341321");

    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"12321321", L"12321321", L"");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"1232 1321", L"1232", L" 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"012341321", L"", L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, e<int>("12321321"), e<int>("12321321"), e<int>(""));
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, e<int>("1232 1321"), e<int>("1232"), e<int>(" 1321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, e<int>(" 12321321"), e<int>(""), e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, e<int>("012341321"), e<int>(""), e<int>("012341321"));

    using P = complete_parser<Joi_Zom_OC>; // Wrap the parser to test its nestability
    ASSERT_PARSE_SUCCESS(P, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(P, L"12321321", L"12321321", L"");
    ASSERT_PARSE_SUCCESS(P, e<int>("12321321"), e<int>("12321321"), e<int>(""));
}

TEST("join_zero_or_more_basic", "zero_or_more_parser<none_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "012341321", "0", "12341321");

    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"12321321", L"", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"1232 1321", L"", L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"12341321", L"", L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"012341321", L"0", L"12341321");

    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, e<int>("12321321"), e<int>(""), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, e<int>("1232 1321"), e<int>(""), e<int>("1232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, e<int>(" 12321321"), e<int>(" "), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, e<int>("12341321"), e<int>(""), e<int>("12341321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, e<int>("012341321"), e<int>("0"), e<int>("12341321"));

    using P = complete_parser<Joi_Zom_NC>; // Wrap the parser to test its nestability
    ASSERT_PARSE_SUCCESS(P, "45654654", "45654654", "");
    ASSERT_PARSE_SUCCESS(P, L"45654654", L"45654654", L"");
    ASSERT_PARSE_SUCCESS(P, e<int>("45654654"), e<int>("45654654"), e<int>(""));
}

TEST("join_zero_or_more_basic", "zero_or_more_parser<all_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "012341321", "", "012341321");

    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"012341321", L"", L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_Zom_L, e<int>("12321321"), e<int>("123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, e<int>("12312321321"), e<int>("123123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, e<int>("1232 1321"), e<int>("123"), e<int>("2 1321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, e<int>(" 12321321"), e<int>(""), e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, e<int>("012341321"), e<int>(""), e<int>("012341321"));

    using P = complete_parser<Joi_Zom_L>; // Wrap the parser to test its nestability
    ASSERT_PARSE_SUCCESS(P, "123123123", "123123123", "");
    ASSERT_PARSE_SUCCESS(P, L"123123123", L"123123123", L"");
    ASSERT_PARSE_SUCCESS(P, e<int>("123123123"), e<int>("123123123"), e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
