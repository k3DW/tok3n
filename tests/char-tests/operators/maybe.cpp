#include "samples.h"

FIXTURE("maybe operator");

TEST("maybe operator", "~Maybe")
{
	ASSERT_PARSER_VALUES_EQ(~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~~may4, may4);
}

TEST("maybe operator", "~OneOrMore")
{
	ASSERT_PARSER_VALUES_EQ(~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~oom4, zom4);
}

TEST("maybe operator", "~ZeroOrMore")
{
	ASSERT_PARSER_VALUES_EQ(~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~zom4, zom4);
}

TEST("maybe operator", "non consteval")
{
	(~any1).parse(TT("abc"));
}
