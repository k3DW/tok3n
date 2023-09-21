#include "pch.h"

FIXTURE("JoinMaybeBasic");

using Joi_May_OC = Join<Maybe<AnyOf<"123">>>;
using Joi_May_NC = Join<Maybe<NoneOf<"123">>>;
using Joi_May_L  = Join<Maybe<Literal<"123">>>;

TEST("JoinMaybeBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_May_OC, JoinType, Output<char>);
    ASSERT_IS_PARSER(Joi_May_NC, JoinType, Output<char>);
    ASSERT_IS_PARSER(Joi_May_L, JoinType, Output<char>);
}

TEST("JoinMaybeBasic", "Maybe<AnyOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12321321", "1", "2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "1232 1321", "1", "232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12341321", "1", "2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "012341321", "", "012341321");
}

TEST("JoinMaybeBasic", "Maybe<NoneOf>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "012341321", "0", "12341321");
}

TEST("JoinMaybeBasic", "Maybe<Literal>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12312321321", "123", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "012341321", "", "012341321");
}
