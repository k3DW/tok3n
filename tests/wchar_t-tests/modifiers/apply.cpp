#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("apply modifier");

TEST("apply modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(apt1, apply<func3_apply>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(apt2, apply<func4_apply(3)>(+abc >> ~(abc | qq)));
	ASSERT_PARSER_VALUES_NE(apt2, apply<func4_apply(2)>(+abc >> ~(abc | qq)));
}

TEST("apply modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(apt1, (abc >> *qq) % apply<func3_apply>);
	ASSERT_PARSER_VALUES_EQ(apt2, (+abc >> ~(abc | qq)) % apply<func4_apply(3)>);
	ASSERT_PARSER_VALUES_NE(apt2, (+abc >> ~(abc | qq)) % apply<func4_apply(2)>);
}
