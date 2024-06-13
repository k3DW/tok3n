#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("delimit modifier");

TEST("delimit modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(del1, delimit(abc, comma));
	ASSERT_PARSER_VALUES_EQ(del2, delimit(abc, spacedot));
	ASSERT_PARSER_VALUES_EQ(del3, delimit(qq, comma));
	ASSERT_PARSER_VALUES_EQ(del4, delimit(qq, spacedot));
	ASSERT_PARSER_VALUES_EQ(del5, delimit(comma, abc));
	ASSERT_PARSER_VALUES_EQ(del6, delimit(spacedot, abc));
	ASSERT_PARSER_VALUES_EQ(del7, delimit(comma, qq));
	ASSERT_PARSER_VALUES_EQ(del8, delimit(spacedot, qq));
}

TEST("delimit modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(del1, abc % delimit(comma));
	ASSERT_PARSER_VALUES_EQ(del2, abc % delimit(spacedot));
	ASSERT_PARSER_VALUES_EQ(del3, qq % delimit(comma));
	ASSERT_PARSER_VALUES_EQ(del4, qq % delimit(spacedot));
	ASSERT_PARSER_VALUES_EQ(del5, comma % delimit(abc));
	ASSERT_PARSER_VALUES_EQ(del6, spacedot % delimit(abc));
	ASSERT_PARSER_VALUES_EQ(del7, comma % delimit(qq));
	ASSERT_PARSER_VALUES_EQ(del8, spacedot % delimit(qq));
}

TEST("delimit modifier", "non consteval")
{
	(delimit(any1, any2)).parse(TT("abc"));
	(any1 % delimit(any2)).parse(TT("abc"));
}
