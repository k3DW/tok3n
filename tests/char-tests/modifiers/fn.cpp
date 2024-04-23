#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("fn modifier");

TEST("fn modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(tra1, fn<func1>(+abc));
	ASSERT_PARSER_VALUES_EQ(tra2, fn<func2>(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(tra3, fn<func3>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(tra4, fn<func4(3)>(+abc >> ~(abc | qq)));
	ASSERT_PARSER_VALUES_NE(tra4, fn<func4(2)>(+abc >> ~(abc | qq)));
}

TEST("fn modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(tra1, +abc % fn<func1>);
	ASSERT_PARSER_VALUES_EQ(tra2, ~(abc | qq) % fn<func2>);
	ASSERT_PARSER_VALUES_EQ(tra3, (abc >> *qq) % fn<func3>);
	ASSERT_PARSER_VALUES_EQ(tra4, (+abc >> ~(abc | qq)) % fn<func4(3)>);
	ASSERT_PARSER_VALUES_NE(tra4, (+abc >> ~(abc | qq)) % fn<func4(2)>);
}

TEST("fn modifier", "non consteval")
{
	constexpr auto sink = [](auto&&) {};
	(fn<sink>(any1)).parse("abc");
	(any1 % fn<sink>).parse("abc");
}
