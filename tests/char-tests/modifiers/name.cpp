#include "samples.h"

FIXTURE("name modifier");

// TODO: Fix this `k3::tok3n::name` stuff.
//       * Maybe rename the `Test` member functions
//       * Or maybe make them private, so we can't see anything inside an actual test

TEST("name modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(nam1, k3::tok3n::name<"nam1">(abc));
	ASSERT_PARSER_VALUES_EQ(nam2, k3::tok3n::name<"nam2">(+abc));
	ASSERT_PARSER_VALUES_EQ(nam3, k3::tok3n::name<"nam3">(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(nam4, k3::tok3n::name<"nam4">(abc >> *qq));
}

TEST("name modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(nam1, abc % k3::tok3n::name<"nam1">);
	ASSERT_PARSER_VALUES_EQ(nam2, +abc % k3::tok3n::name<"nam2">);
	ASSERT_PARSER_VALUES_EQ(nam3, ~(abc | qq) % k3::tok3n::name<"nam3">);
	ASSERT_PARSER_VALUES_EQ(nam4, (abc >> *qq) % k3::tok3n::name<"nam4">);
}

TEST("name modifier", "non consteval")
{
	(k3::tok3n::name<"test">(any1)).parse(TT("abc"));
	(any1 % k3::tok3n::name<"test">).parse(TT("abc"));
}



#define NAME_MODIFIER_ASSERTER(P)                                                            \
    ASSERT_MODIFIER_CALLABLE_R(k3::tok3n::name<"test1">, (P{}), (Named<P, "test1">{}));      \
    ASSERT_MODIFIER_CALLABLE_R(k3::tok3n::name<"test2">, (P{}), (Named<P, "test2">{}));      \
	ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, k3::tok3n::name<"test1">, (Named<P, "test1">{})); \
	ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, k3::tok3n::name<"test2">, (Named<P, "test2">{}));

TEST("name modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(NAME_MODIFIER_ASSERTER);
}
