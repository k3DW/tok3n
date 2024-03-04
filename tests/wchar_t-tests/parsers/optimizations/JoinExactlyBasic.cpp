#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("JoinExactlyBasic");

using Joi_Exa_OC  = Join<Exactly<AnyOf<L"123">, Index<2>>>;
using Joi_Exa_NC  = Join<Exactly<NoneOf<L"123">, Index<2>>>;
using Joi_Exa_L   = Join<Exactly<AllOf<L"123">, Index<2>>>;

TEST("JoinExactlyBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Exa_OC, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Exa_NC, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Exa_L, JoinFamily, Output<wchar_t>);
}

TEST("JoinExactlyBasic", "Exactly<AnyOf, 2>")
{
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, L"12321321", L"12", L"321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, L"1232 1321", L"12", L"32 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, L"12341321", L"12", L"341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, L"1012341321");
}

TEST("JoinExactlyBasic", "Exactly<NoneOf, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L" 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"012341321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_NC, L"0012341321", L"00", L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, L"1012341321");
}

TEST("JoinExactlyBasic", "Exactly<AllOf, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L" 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, L"012341321");
}
