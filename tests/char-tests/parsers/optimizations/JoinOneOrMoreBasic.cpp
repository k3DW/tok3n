#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("JoinOneOrMoreBasic");

using Joi_Oom_OC = Join<OneOrMore<AnyOf<"123">>>;
using Joi_Oom_NC = Join<OneOrMore<NoneOf<"123">>>;
using Joi_Oom_L  = Join<OneOrMore<AllOf<"123">>>;

TEST("JoinOneOrMoreBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Oom_OC, char, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_Oom_NC, char, JoinFamily, Output<char>);
    ASSERT_IS_PARSER(Joi_Oom_L, char, JoinFamily, Output<char>);
}

TEST("JoinOneOrMoreBasic", "OneOrMore<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, "012341321");
}

TEST("JoinOneOrMoreBasic", "OneOrMore<NoneOf>")
{
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, "012341321", "0", "12341321");
}

TEST("JoinOneOrMoreBasic", "OneOrMore<AllOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, "012341321");
}
