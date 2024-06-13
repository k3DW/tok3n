#include "pch.h"
#include "char-tests/samples.h"

FIXTURE("JoinMaybeBasic");

using Joi_May_OC = Join<Maybe<AnyOf<TT("123")>>>;
using Joi_May_NC = Join<Maybe<NoneOf<TT("123")>>>;
using Joi_May_L  = Join<Maybe<AllOf<TT("123")>>>;

TEST("JoinMaybeBasic", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Joi_May_OC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_May_NC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_May_L, value_type);

    ASSERT_IS_PARSER(Joi_May_OC, char, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_May_NC, char, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_May_L, char, JoinFamily, Output<char>);

    ASSERT_IS_PARSER(Joi_May_OC, wchar_t, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_May_NC, wchar_t, JoinFamily, Output<wchar_t>);
    ASSERT_IS_PARSER(Joi_May_L, wchar_t, JoinFamily, Output<wchar_t>);

    ASSERT_IS_PARSER(Joi_May_OC, int, JoinFamily, Output<int>);
    ASSERT_IS_PARSER(Joi_May_NC, int, JoinFamily, Output<int>);
    ASSERT_IS_PARSER(Joi_May_L, int, JoinFamily, Output<int>);
}

TEST("JoinMaybeBasic", "Maybe<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12321321", "1", "2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "1232 1321", "1", "232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12341321", "1", "2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "012341321", "", "012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"12321321", L"1", L"2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"1232 1321", L"1", L"232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"12341321", L"1", L"2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, L"012341321", L"", L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("12321321"), e<int>("1"), e<int>("2321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("1232 1321"), e<int>("1"), e<int>("232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>(" 12321321"), e<int>(""), e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("12341321"), e<int>("1"), e<int>("2341321"));
    ASSERT_PARSE_SUCCESS(Joi_May_OC, e<int>("012341321"), e<int>(""), e<int>("012341321"));
}

TEST("JoinMaybeBasic", "Maybe<NoneOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "012341321", "0", "12341321");

    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"12321321", L"", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"1232 1321", L"", L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"12341321", L"", L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, L"012341321", L"0", L"12341321");

    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("12321321"), e<int>(""), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("1232 1321"), e<int>(""), e<int>("1232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>(" 12321321"), e<int>(" "), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("12341321"), e<int>(""), e<int>("12341321"));
    ASSERT_PARSE_SUCCESS(Joi_May_NC, e<int>("012341321"), e<int>("0"), e<int>("12341321"));
}

TEST("JoinMaybeBasic", "Maybe<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12312321321", "123", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "012341321", "", "012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12312321321", L"123", L"12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L" 12321321", L"", L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, L"012341321", L"", L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("12321321"), e<int>("123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("12312321321"), e<int>("123"), e<int>("12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("1232 1321"), e<int>("123"), e<int>("2 1321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>(" 12321321"), e<int>(""), e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_SUCCESS(Joi_May_L, e<int>("012341321"), e<int>(""), e<int>("012341321"));
}
