#include "pch.h"

FIXTURE("JoinContiguous");

using Joi_Oom_OC  = Join<OneOrMore<OneChar<"123">>>;
using Joi_Oom_NC  = Join<OneOrMore<NotChar<"123">>>;
using Joi_Oom_L   = Join<OneOrMore<Literal<"123">>>;
using Joi_Zom_OC  = Join<ZeroOrMore<OneChar<"123">>>;
using Joi_Zom_NC  = Join<ZeroOrMore<NotChar<"123">>>;
using Joi_Zom_L   = Join<ZeroOrMore<Literal<"123">>>;
using Joi_May_OC  = Join<Maybe<OneChar<"123">>>;
using Joi_May_NC  = Join<Maybe<NotChar<"123">>>;
using Joi_May_L   = Join<Maybe<Literal<"123">>>;
using Joi_Exa_OC  = Join<Exactly<OneChar<"123">, Index<2>>>;
using Joi_Exa_NC  = Join<Exactly<NotChar<"123">, Index<2>>>;
using Joi_Exa_L   = Join<Exactly<Literal<"123">, Index<2>>>;

TEST("JoinContiguous", "Requirements")
{
    ASSERT_IS_PARSER(Joi_Oom_OC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Oom_NC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Oom_L, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Zom_OC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Zom_NC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Zom_L, JoinType, Output);
    ASSERT_IS_PARSER(Joi_May_OC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_May_NC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_May_L, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Exa_OC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Exa_NC, JoinType, Output);
    ASSERT_IS_PARSER(Joi_Exa_L, JoinType, Output);
}

TEST("JoinContiguous", "OneOrMore<OneChar>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, "012341321");
}

TEST("JoinContiguous", "OneOrMore<NotChar>")
{
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, "012341321", "0", "12341321");
}

TEST("JoinContiguous", "OneOrMore<Literal>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, "012341321");
}

TEST("JoinContiguous", "ZeroOrMore<OneChar>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_OC, "012341321", "", "012341321");
}

TEST("JoinContiguous", "ZeroOrMore<NotChar>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_NC, "012341321", "0", "12341321");
}

TEST("JoinContiguous", "ZeroOrMore<Literal>")
{
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_Zom_L, "012341321", "", "012341321");
}

TEST("JoinContiguous", "Maybe<OneChar>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12321321", "1", "2321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "1232 1321", "1", "232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "12341321", "1", "2341321");
    ASSERT_PARSE_SUCCESS(Joi_May_OC, "012341321", "", "012341321");
}

TEST("JoinContiguous", "Maybe<NotChar>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12321321", "", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "1232 1321", "", "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "12341321", "", "12341321");
    ASSERT_PARSE_SUCCESS(Joi_May_NC, "012341321", "0", "12341321");
}

TEST("JoinContiguous", "Maybe<Literal>")
{
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12312321321", "123", "12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, " 12321321", "", " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "12341321", "123", "41321");
    ASSERT_PARSE_SUCCESS(Joi_May_L, "012341321", "", "012341321");
}

TEST("JoinContiguous", "Exactly<OneChar, 2>")
{
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "12321321", "12", "321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "1232 1321", "12", "32 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_OC, "12341321", "12", "341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "0012341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_OC, "1012341321");
}

TEST("JoinContiguous", "Exactly<NotChar, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "012341321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_NC, "0012341321", "00", "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_NC, "1012341321");
}

TEST("JoinContiguous", "Exactly<Literal, 2>")
{
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12321321");
    ASSERT_PARSE_SUCCESS(Joi_Exa_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "1232 1321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, " 12321321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "12341321");
    ASSERT_PARSE_FAILURE(Joi_Exa_L, "012341321");
}
