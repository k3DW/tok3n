#include "pch.h"
#include "char-tests/samples.h"

FIXTURE("delimit_keep modifier");

TEST("delimit_keep modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(dek1, delimit_keep(abc, comma));
	ASSERT_PARSER_VALUES_EQ(dek2, delimit_keep(abc, spacedot));
	ASSERT_PARSER_VALUES_EQ(dek3, delimit_keep(qq, comma));
	ASSERT_PARSER_VALUES_EQ(dek4, delimit_keep(qq, spacedot));
	ASSERT_PARSER_VALUES_EQ(dek5, delimit_keep(comma, abc));
	ASSERT_PARSER_VALUES_EQ(dek6, delimit_keep(spacedot, abc));
	ASSERT_PARSER_VALUES_EQ(dek7, delimit_keep(comma, qq));
	ASSERT_PARSER_VALUES_EQ(dek8, delimit_keep(spacedot, qq));
}

TEST("delimit_keep modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(dek1, abc % delimit_keep(comma));
	ASSERT_PARSER_VALUES_EQ(dek2, abc % delimit_keep(spacedot));
	ASSERT_PARSER_VALUES_EQ(dek3, qq % delimit_keep(comma));
	ASSERT_PARSER_VALUES_EQ(dek4, qq % delimit_keep(spacedot));
	ASSERT_PARSER_VALUES_EQ(dek5, comma % delimit_keep(abc));
	ASSERT_PARSER_VALUES_EQ(dek6, spacedot % delimit_keep(abc));
	ASSERT_PARSER_VALUES_EQ(dek7, comma % delimit_keep(qq));
	ASSERT_PARSER_VALUES_EQ(dek8, spacedot % delimit_keep(qq));
}

TEST("delimit_keep modifier", "non consteval")
{
	(delimit_keep(any1, any2)).parse("abc");
	(any1 % delimit_keep(any2)).parse("abc");
}
