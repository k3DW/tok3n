#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("JoinMaybeBasic");

using Joi_May_OC = Join<Maybe<AnyOf<L"123">>>;
using Joi_May_NC = Join<Maybe<NoneOf<L"123">>>;
using Joi_May_L  = Join<Maybe<AllOf<L"123">>>;

TEST("JoinMaybeBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_May_OC, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_May_NC, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_May_L, JoinFamily, Output<wchar_t>);
}

TEST("JoinMaybeBasic", "Maybe<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"12321321", L"1", L"2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"1232 1321", L"1", L"232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"12341321", L"1", L"2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"012341321", L"", L"012341321");
}

TEST("JoinMaybeBasic", "Maybe<NoneOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"12321321", L"", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"1232 1321", L"", L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"12341321", L"", L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"012341321", L"0", L"12341321");
}

TEST("JoinMaybeBasic", "Maybe<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12312321321", L"123", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"012341321", L"", L"012341321");
}
