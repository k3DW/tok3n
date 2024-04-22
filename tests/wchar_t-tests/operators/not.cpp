#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("not operator");

TEST("not operator", "!AnyOf")
{
	ASSERT_PARSER_VALUES_EQ(!any1, none1);
	ASSERT_PARSER_VALUES_EQ(!any2, none2);
	ASSERT_PARSER_VALUES_EQ(!any3, none3);
	ASSERT_PARSER_VALUES_EQ(!!any1, any1);
	ASSERT_PARSER_VALUES_EQ(!!any2, any2);
	ASSERT_PARSER_VALUES_EQ(!!any3, any3);
}

TEST("not operator", "!NoneOf")
{
	ASSERT_PARSER_VALUES_EQ(!none1, any1);
	ASSERT_PARSER_VALUES_EQ(!none2, any2);
	ASSERT_PARSER_VALUES_EQ(!none3, any3);
	ASSERT_PARSER_VALUES_EQ(!!none1, none1);
	ASSERT_PARSER_VALUES_EQ(!!none2, none2);
	ASSERT_PARSER_VALUES_EQ(!!none3, none3);
}
