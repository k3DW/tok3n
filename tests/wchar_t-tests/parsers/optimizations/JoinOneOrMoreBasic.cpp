#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("JoinOneOrMoreBasic");

using Joi_Oom_OC = Join<OneOrMore<AnyOf<TT("123")>>>;
using Joi_Oom_NC = Join<OneOrMore<NoneOf<TT("123")>>>;
using Joi_Oom_L  = Join<OneOrMore<AllOf<TT("123")>>>;

TEST("JoinOneOrMoreBasic", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Joi_Oom_OC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Oom_NC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Oom_L, value_type);

    ASSERT_IS_PARSER(Joi_Oom_OC, char, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_Oom_NC, char, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_Oom_L, char, JoinFamily, Output<char>);

    ASSERT_IS_PARSER(Joi_Oom_OC, wchar_t, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Oom_NC, wchar_t, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_Oom_L, wchar_t, JoinFamily, Output<wchar_t>);

    ASSERT_IS_PARSER(Joi_Oom_OC, int, JoinFamily, Output<int>);
    ASSERT_IS_PARSER(Joi_Oom_NC, int, JoinFamily, Output<int>);
    ASSERT_IS_PARSER(Joi_Oom_L, int, JoinFamily, Output<int>);
}

TEST("JoinOneOrMoreBasic", "OneOrMore<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, "012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"12321321", L"12321321", L"");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"1232 1321", L"1232", L" 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"12341321", L"123", L"41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, e<int>("12321321"), e<int>("12321321"), e<int>(""));
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, e<int>("1232 1321"), e<int>("1232"), e<int>(" 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, e<int>("012341321"));
}

TEST("JoinOneOrMoreBasic", "OneOrMore<NoneOf>")
{
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, "012341321", "0", "12341321");

    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, L"012341321", L"0", L"12341321");

    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("1232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, e<int>(" 12321321"), e<int>(" "), e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("12341321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, e<int>("012341321"), e<int>("0"), e<int>("12341321"));
}

TEST("JoinOneOrMoreBasic", "OneOrMore<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, "012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("12321321"), e<int>("123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("12312321321"), e<int>("123123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("1232 1321"), e<int>("123"), e<int>("2 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, e<int>("012341321"));
}
