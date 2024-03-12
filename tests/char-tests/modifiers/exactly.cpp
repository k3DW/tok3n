#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("exactly modifier");

TEST("exactly modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(exa1, exactly<3>(all1));
	ASSERT_PARSER_VALUES_EQ(exa2, exactly<5>(any1));
	ASSERT_PARSER_VALUES_EQ(exa3, exactly<4>(all1 | any1));
	ASSERT_PARSER_VALUES_EQ(exa4, exactly<2>(all1 >> any1));
}

TEST("exactly modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(exa1, all1 % exactly<3>);
	ASSERT_PARSER_VALUES_EQ(exa2, any1 % exactly<5>);
	ASSERT_PARSER_VALUES_EQ(exa3, (all1 | any1) % exactly<4>);
	ASSERT_PARSER_VALUES_EQ(exa4, (all1 >> any1) % exactly<2>);
}
