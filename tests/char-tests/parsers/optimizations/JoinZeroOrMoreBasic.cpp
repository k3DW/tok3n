#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("JoinZeroOrMoreBasic");

using Joi_Zom_OC = Join<ZeroOrMore<AnyOf<"123">>>;
using Joi_Zom_NC = Join<ZeroOrMore<NoneOf<"123">>>;
using Joi_Zom_L  = Join<ZeroOrMore<AllOf<"123">>>;

TEST("JoinZeroOrMoreBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Zom_OC, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_Zom_NC, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_Zom_L, JoinFamily, Output<char>);
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "012341321", "", "012341321");
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<NoneOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "012341321", "0", "12341321");
}

TEST("JoinZeroOrMoreBasic", "ZeroOrMore<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "012341321", "", "012341321");
}
