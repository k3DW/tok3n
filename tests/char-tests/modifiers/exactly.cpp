#include "samples.h"

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

TEST("exactly modifier", "non consteval")
{
	(exactly<2>(any1)).parse(TT("abc"));
	(any1 % exactly<2>).parse(TT("abc"));
}



#define EXACTLY_MODIFIER_ASSERTER(P)                                                       \
	[]<Parser PP>(PP) {                                                                    \
		DEP_ASSERT_MODIFIER_CALLABLE_R(exactly<2>, (PP{}), (Exactly<PP, Index<2>>{}),      \
				                       exactly<2>, (P{}),  (Exactly<P, Index<2>>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, exactly<2>, (Exactly<PP, Index<2>>{}), \
				                              P{},  exactly<2>, (Exactly<P, Index<2>>{})); \
	}(P{});

TEST("exactly modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(EXACTLY_MODIFIER_ASSERTER);
}
