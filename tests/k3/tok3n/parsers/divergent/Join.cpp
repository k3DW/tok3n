#include "pch.h"

FIXTURE("Join");

TEST("Join", "Requirements")
{
	ASSERT_IS_PARSER(Joi1, JoinType, Output<char>);
	ASSERT_IS_PARSER(Joi2, JoinType, Output<char>);
	ASSERT_IS_PARSER(Joi3, JoinType, Output<char>);
	ASSERT_IS_PARSER(Joi4, JoinType, Output<char>);
	ASSERT_IS_PARSER(Joi5, JoinType, Output<char>);
}

TEST("Join", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Joi1, "abcabc", "abc", "abc");
	ASSERT_PARSE_FAILURE(Joi1, "Abcabc");
	ASSERT_PARSE_FAILURE(Joi1, " abcabc");

	ASSERT_PARSE_SUCCESS(Joi2, "abcabcabcab", "abcabcabc", "ab");
	ASSERT_PARSE_FAILURE(Joi2, "");
	ASSERT_PARSE_FAILURE(Joi2, "ab");
	ASSERT_PARSE_SUCCESS(Joi2, "abc", "abc", "");

	ASSERT_PARSE_SUCCESS(Joi3, "abcabc", "abc", "abc");
	ASSERT_PARSE_SUCCESS(Joi3, "a??bcabc", "", "a??bcabc");
	ASSERT_PARSE_SUCCESS(Joi3, "", "", "");
	ASSERT_PARSE_SUCCESS(Joi3, "??abcabc", "??", "abcabc");
	ASSERT_PARSE_SUCCESS(Joi3, " ??abcabc", "", " ??abcabc");

	ASSERT_PARSE_SUCCESS(Joi4, "abc???????", "abc??????", "?");
	ASSERT_PARSE_FAILURE(Joi4, "??abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, "abc??abc???????", "abc??", "abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, "abc ??abc???????", "abc", " ??abc???????");
	ASSERT_PARSE_FAILURE(Joi4, "");

	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc??", "abcabcabcabc??", "");
	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc", "abcabcabcabc", "");
	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc ??", "abcabcabcabc", " ??");
	ASSERT_PARSE_SUCCESS(Joi5, "abc", "abc", "");
	ASSERT_PARSE_FAILURE(Joi5, " abc");
	ASSERT_PARSE_FAILURE(Joi5, "");
}

TEST("Join", "Contiguous empty strings")
{
	using J1 = Join<Maybe<Choice<ABC, QQ>>>;
	using J2 = Join<ZeroOrMore<Sequence<L1, OC2>>>;

	using P = Join<Sequence<Literal<"**start**">, J1, J2, Literal<"__end__">>>;

	ASSERT_PARSE_SUCCESS(P, "**start**__end__", "**start**__end__", "");
}
