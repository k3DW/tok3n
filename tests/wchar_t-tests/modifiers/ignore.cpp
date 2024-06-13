#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("ignore modifier");

TEST("ignore modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(ign1, ignore(abc));
	ASSERT_PARSER_VALUES_EQ(ign2, ignore(+abc));
	ASSERT_PARSER_VALUES_EQ(ign3, ignore(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(ign4, ignore(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(ign5, ignore(+abc >> ~(abc | qq)));
}

TEST("ignore modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(ign1, abc % ignore);
	ASSERT_PARSER_VALUES_EQ(ign2, +abc % ignore);
	ASSERT_PARSER_VALUES_EQ(ign3, ~(abc | qq) % ignore);
	ASSERT_PARSER_VALUES_EQ(ign4, (abc >> *qq) % ignore);
	ASSERT_PARSER_VALUES_EQ(ign5, (+abc >> ~(abc | qq)) % ignore);
}

TEST("ignore modifier", "idempotent")
{
	ASSERT_PARSER_VALUES_EQ(ign1, ignore(ign1));
	ASSERT_PARSER_VALUES_EQ(ign2, ignore(ign2));
	ASSERT_PARSER_VALUES_EQ(ign3, ignore(ign3));
	ASSERT_PARSER_VALUES_EQ(ign4, ignore(ign4));
	ASSERT_PARSER_VALUES_EQ(ign5, ignore(ign5));
	ASSERT_PARSER_VALUES_EQ(ign1, ign1 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign2, ign2 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign3, ign3 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign4, ign4 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign5, ign5 % ignore);
}

TEST("ignore modifier", "non consteval")
{
	(ignore(any1)).parse(L"abc");
	(any1 % ignore).parse(L"abc");
}
