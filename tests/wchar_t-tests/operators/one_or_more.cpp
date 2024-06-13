#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("one_or_more operator");

TEST("one_or_more operator", "+Maybe")
{
	ASSERT_PARSER_VALUES_EQ(+may1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ +may1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ + +may1, zom1);
	ASSERT_PARSER_VALUES_EQ(+may2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ +may2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ + +may2, zom2);
	ASSERT_PARSER_VALUES_EQ(+may3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ +may3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ + +may3, zom3);
	ASSERT_PARSER_VALUES_EQ(+may4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ +may4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ + +may4, zom4);
}

TEST("one_or_more operator", "+OneOrMore")
{
	ASSERT_PARSER_VALUES_EQ(+oom1, oom1);
	ASSERT_PARSER_VALUES_EQ(+ +oom1, oom1);
	ASSERT_PARSER_VALUES_EQ(+ + +oom1, oom1);
	ASSERT_PARSER_VALUES_EQ(+oom2, oom2);
	ASSERT_PARSER_VALUES_EQ(+ +oom2, oom2);
	ASSERT_PARSER_VALUES_EQ(+ + +oom2, oom2);
	ASSERT_PARSER_VALUES_EQ(+oom3, oom3);
	ASSERT_PARSER_VALUES_EQ(+ +oom3, oom3);
	ASSERT_PARSER_VALUES_EQ(+ + +oom3, oom3);
	ASSERT_PARSER_VALUES_EQ(+oom4, oom4);
	ASSERT_PARSER_VALUES_EQ(+ +oom4, oom4);
	ASSERT_PARSER_VALUES_EQ(+ + +oom4, oom4);
}

TEST("one_or_more operator", "+ZeroOrMore")
{
	ASSERT_PARSER_VALUES_EQ(+zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ +zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ + +zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(+zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ +zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ + +zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(+zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ +zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ + +zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(+zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ +zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ + +zom4, zom4);
}

TEST("one_or_more operator", "non consteval")
{
	(+any1).parse(L"abc");
}
