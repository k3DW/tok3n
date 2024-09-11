#include "samples.h"

FIXTURE("join modifier");

TEST("join modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(joi1, join(abc));
	ASSERT_PARSER_VALUES_NE(abc, join(abc));
	ASSERT_PARSER_VALUES_EQ(joi2, join(+abc));
	ASSERT_PARSER_VALUES_EQ(joi3, join(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(joi4, join(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(joi5, join(+abc >> ~(abc | qq)));
}

TEST("join modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(joi1, abc % join);
	ASSERT_PARSER_VALUES_NE(abc, abc % join);
	ASSERT_PARSER_VALUES_EQ(joi2, +abc % join);
	ASSERT_PARSER_VALUES_EQ(joi3, ~(abc | qq) % join);
	ASSERT_PARSER_VALUES_EQ(joi4, (abc >> *qq) % join);
	ASSERT_PARSER_VALUES_EQ(joi5, (+abc >> ~(abc | qq)) % join);
}

TEST("join modifier", "idempotent")
{
	ASSERT_PARSER_VALUES_EQ(joi1, join(joi1));
	ASSERT_PARSER_VALUES_EQ(joi2, join(joi2));
	ASSERT_PARSER_VALUES_EQ(joi3, join(joi3));
	ASSERT_PARSER_VALUES_EQ(joi4, join(joi4));
	ASSERT_PARSER_VALUES_EQ(joi5, join(joi5));
	ASSERT_PARSER_VALUES_EQ(joi1, joi1 % join);
	ASSERT_PARSER_VALUES_EQ(joi2, joi2 % join);
	ASSERT_PARSER_VALUES_EQ(joi3, joi3 % join);
	ASSERT_PARSER_VALUES_EQ(joi4, joi4 % join);
	ASSERT_PARSER_VALUES_EQ(joi5, joi5 % join);
}

TEST("join modifier", "non consteval")
{
	(join(any1)).parse(TT("abc"));
	(any1 % join).parse(TT("abc"));
}



#define JOIN_MODIFIER_ASSERTER(P)                                         \
	[]<detail::parser PP>(PP) {                                           \
		if constexpr (PP::family == detail::join_family)                  \
		{                                                                 \
			DEP_ASSERT_MODIFIER_CALLABLE_R(join, (PP{}), PP{},            \
				                           join, (P{}),  P{});            \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, join, PP{},       \
				                                  P{},  join, P{});       \
		}                                                                 \
		else                                                              \
		{                                                                 \
			DEP_ASSERT_MODIFIER_CALLABLE_R(join, (PP{}), Join<PP>{},      \
				                           join, (P{}),  Join<P>{});      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, join, Join<PP>{}, \
				                                  P{},  join, Join<P>{}); \
		}                                                                 \
	}(P{});

TEST("join modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(JOIN_MODIFIER_ASSERTER);
}
