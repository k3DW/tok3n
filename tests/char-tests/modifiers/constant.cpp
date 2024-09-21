#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

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

TEST("constant modifier", "non consteval")
{
	(constant<0>(any1)).parse(TT("abc"));
	(any1 % constant<0>).parse(TT("abc"));
}



#define CONSTANT_MODIFIER_ASSERTER(P)                                                                  \
	ASSERT_MODIFIER_CALLABLE_R(constant<0>, (P{}), (constant_parser<P, integral_constant<0>>{}));      \
	ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, constant<0>, (constant_parser<P, integral_constant<0>>{}));

TEST("constant modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(CONSTANT_MODIFIER_ASSERTER);
}
