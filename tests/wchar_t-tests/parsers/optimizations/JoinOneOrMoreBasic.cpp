#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("JoinOneOrMoreBasic");

using Joi_Oom_OC = Join<OneOrMore<AnyOf<L"123">>>;
using Joi_Oom_NC = Join<OneOrMore<NoneOf<L"123">>>;
using Joi_Oom_L  = Join<OneOrMore<AllOf<L"123">>>;

TEST("JoinOneOrMoreBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Oom_OC, wchar_t, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Oom_NC, wchar_t, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Oom_L, wchar_t, JoinFamily, Output<wchar_t>);
}

TEST("JoinOneOrMoreBasic", "OneOrMore<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"12321321", L"12321321", L"");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"1232 1321", L"1232", L" 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"12341321", L"123", L"41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L"012341321");
}

TEST("JoinOneOrMoreBasic", "OneOrMore<NoneOf>")
{
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, L"012341321", L"0", L"12341321");
}

TEST("JoinOneOrMoreBasic", "OneOrMore<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L"012341321");
}
