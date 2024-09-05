#include "samples.h"

FIXTURE("defaulted modifier");

TEST("defaulted modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(def1, defaulted<int>(+abc));
	ASSERT_PARSER_VALUES_EQ(def2, defaulted<Class3>(~(abc | qq)));
}

TEST("defaulted modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(def1, +abc % defaulted<int>);
	ASSERT_PARSER_VALUES_EQ(def2, ~(abc | qq) % defaulted<Class3>);
}

TEST("defaulted modifier", "non consteval")
{
	(defaulted<int>(any1)).parse(TT("abc"));
	(any1 % defaulted<int>).parse(TT("abc"));
}



#define DEFAULTED_MODIFIER_ASSERTER(P)                                                        \
	ASSERT_MODIFIER_CALLABLE_R(defaulted<bool>, (P{}), (aliases::Defaulted<P, bool>{}));      \
	ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, defaulted<bool>, (aliases::Defaulted<P, bool>{}));

TEST("defaulted modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(DEFAULTED_MODIFIER_ASSERTER);
}
