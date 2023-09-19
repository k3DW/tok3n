#include "pch.h"

FIXTURE("JoinExactlyBasic");

using Joi_Exa_OC  = Join<Exactly<OneChar<"123">, Index<2>>>;
using Joi_Exa_NC  = Join<Exactly<NotChar<"123">, Index<2>>>;
using Joi_Exa_L   = Join<Exactly<Literal<"123">, Index<2>>>;

TEST("JoinExactlyBasic", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Exa_OC, JoinType, Output<char>);
    ASSERT_IS_PARSER(Joi_Exa_NC, JoinType, Output<char>);
    ASSERT_IS_PARSER(Joi_Exa_L, JoinType, Output<char>);
}

TEST("JoinExactlyBasic", "Exactly<OneChar, 2>")
{
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "12321321", "12", "321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "1232 1321", "12", "32 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "12341321", "12", "341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "1012341321");
}

TEST("JoinExactlyBasic", "Exactly<NotChar, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "012341321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_NC, "0012341321", "00", "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1012341321");
}

TEST("JoinExactlyBasic", "Exactly<Literal, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "012341321");
}
