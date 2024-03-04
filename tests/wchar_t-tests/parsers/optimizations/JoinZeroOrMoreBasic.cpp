#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("JoinZeroOrMoreBasic");

using Joi_Zom_OC = Join<ZeroOrMore<AnyOf<L"123">>>;
using Joi_Zom_NC = Join<ZeroOrMore<NoneOf<L"123">>>;
using Joi_Zom_L  = Join<ZeroOrMore<AllOf<L"123">>>;

TEST("JoinZeroOrMoreBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Zom_OC, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Zom_NC, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Zom_L, JoinFamily, Output<wchar_t>);
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"12321321", L"12321321", L"");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"1232 1321", L"1232", L" 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, L"012341321", L"", L"012341321");
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<NoneOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"12321321", L"", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"1232 1321", L"", L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"12341321", L"", L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, L"012341321", L"0", L"12341321");
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, L"012341321", L"", L"012341321");
}
