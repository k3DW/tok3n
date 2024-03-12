#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("constant modifier");

TEST("constant modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(con1, constant<1>(+abc));
	ASSERT_PARSER_VALUES_EQ(con2, constant<'t'>(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(con3, constant<true>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(con4, constant<nullptr>(+abc >> ~(abc | qq)));
}

TEST("constant modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(con1, +abc % constant<1>);
	ASSERT_PARSER_VALUES_EQ(con2, ~(abc | qq) % constant<'t'>);
	ASSERT_PARSER_VALUES_EQ(con3, (abc >> *qq) % constant<true>);
	ASSERT_PARSER_VALUES_EQ(con4, (+abc >> ~(abc | qq)) % constant<nullptr>);
}
