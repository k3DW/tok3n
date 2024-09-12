#include "samples.h"

FIXTURE("JoinZeroOrMoreBasic");

using Joi_Zom_OC = Join<ZeroOrMore<AnyOf<TT("123")>>>;
using Joi_Zom_NC = Join<ZeroOrMore<NoneOf<TT("123")>>>;
using Joi_Zom_L  = Join<ZeroOrMore<AllOf<TT("123")>>>;

TEST("JoinZeroOrMoreBasic", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Joi_Zom_OC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Zom_NC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Zom_L, value_type);

    ASSERT_IS_PARSER(Joi_Zom_OC, char, detail::join_family, detail::output_span<char>);
    ASSERT_IS_PARSER(Joi_Zom_NC, char, detail::join_family, detail::output_span<char>);
    ASSERT_IS_PARSER(Joi_Zom_L, char, detail::join_family, detail::output_span<char>);

    ASSERT_IS_PARSER(Joi_Zom_OC, wchar_t, detail::join_family, detail::output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Zom_NC, wchar_t, detail::join_family, detail::output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Zom_L, wchar_t, detail::join_family, detail::output_span<wchar_t>);

    ASSERT_IS_PARSER(Joi_Zom_OC, int, detail::join_family, detail::output_span<int>);
    ASSERT_IS_PARSER(Joi_Zom_NC, int, detail::join_family, detail::output_span<int>);
    ASSERT_IS_PARSER(Joi_Zom_L, int, detail::join_family, detail::output_span<int>);
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<AnyOf>")
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
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<NoneOf>")
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
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<AllOf>")
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
}
