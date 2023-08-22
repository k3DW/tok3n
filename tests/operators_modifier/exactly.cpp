#include "pch.h"

FIXTURE("exactly modifier");

TEST("exactly modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(exa1, exactly<3>(l1));
	ASSERT_PARSER_VALUES_EQ(exa2, exactly<5>(oc1));
	ASSERT_PARSER_VALUES_EQ(exa3, exactly<4>(l1 | oc1));
	ASSERT_PARSER_VALUES_EQ(exa4, exactly<2>(l1 >> oc1));
}

TEST("exactly modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(exa1, l1 % exactly<3>);
	ASSERT_PARSER_VALUES_EQ(exa2, oc1 % exactly<5>);
	ASSERT_PARSER_VALUES_EQ(exa3, (l1 | oc1) % exactly<4>);
	ASSERT_PARSER_VALUES_EQ(exa4, (l1 >> oc1) % exactly<2>);
}



#define EXACTLY_MODIFIER_ASSERTER(P)                                                           \
	[&]<Parser PP>(PP) {                                                                       \
		if constexpr (std::same_as<typename PP::result_type, void>)                            \
		{                                                                                      \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(exactly<2>, (PP{}),                               \
				                             exactly<2>, (P{}));                               \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, exactly<2>,                          \
				                                    P{},  exactly<2>);                         \
		}                                                                                      \
		else                                                                                   \
		{                                                                                      \
			DEP_ASSERT_MODIFIER_CALLABLE_R(exactly<2>, (PP{}), (Exactly<PP, Index<2>>{}),      \
				                           exactly<2>, (P{}),  (Exactly<P, Index<2>>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, exactly<2>, (Exactly<PP, Index<2>>{}), \
				                                  P{},  exactly<2>, (Exactly<P, Index<2>>{})); \
		}                                                                                      \
	}(P{});

TEST("exactly modifier", "modify anything")
{
	DO_TO_SAMPLES_ALL(EXACTLY_MODIFIER_ASSERTER);
}
