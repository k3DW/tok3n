#include "pch.h"

FIXTURE("delimit modifier");

TEST("delimit modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(del1, delimit(abc, comma));
	ASSERT_PARSER_VALUES_EQ(del2, delimit(abc, spacedot));
	ASSERT_PARSER_VALUES_EQ(del3, delimit(qq, comma));
	ASSERT_PARSER_VALUES_EQ(del4, delimit(qq, spacedot));
	ASSERT_PARSER_VALUES_EQ(del5, delimit(comma, abc));
	ASSERT_PARSER_VALUES_EQ(del6, delimit(spacedot, abc));
	ASSERT_PARSER_VALUES_EQ(del7, delimit(comma, qq));
	ASSERT_PARSER_VALUES_EQ(del8, delimit(spacedot, qq));
}

TEST("delimit modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(del1, abc % delimit(comma));
	ASSERT_PARSER_VALUES_EQ(del2, abc % delimit(spacedot));
	ASSERT_PARSER_VALUES_EQ(del3, qq % delimit(comma));
	ASSERT_PARSER_VALUES_EQ(del4, qq % delimit(spacedot));
	ASSERT_PARSER_VALUES_EQ(del5, comma % delimit(abc));
	ASSERT_PARSER_VALUES_EQ(del6, spacedot % delimit(abc));
	ASSERT_PARSER_VALUES_EQ(del7, comma % delimit(qq));
	ASSERT_PARSER_VALUES_EQ(del8, spacedot % delimit(qq));
}



#define DELIMIT_MODIFIER_ASSERTER(P)                                                                   \
	[&]<Parser PP>(PP) {                                                                               \
		if constexpr (std::same_as<typename PP::result_type, void>)                                    \
		{                                                                                              \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(delimit, (PP{}, comma),                                   \
				                             delimit, (P{}, comma));                                   \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, delimit(comma),                              \
				                                    P{},  delimit(comma));                             \
		}                                                                                              \
		else                                                                                           \
		{                                                                                              \
			DEP_ASSERT_MODIFIER_CALLABLE_R(delimit, (PP{}, comma), (Delimit<PP, Comma, False>{}),      \
				                           delimit, (P{}, comma),  (Delimit<P, Comma, False>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit(comma), (Delimit<PP, Comma, False>{}), \
				                                  P{},  delimit(comma), (Delimit<P, Comma, False>{})); \
		}                                                                                              \
	}(P{});

TEST("delimit modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(DELIMIT_MODIFIER_ASSERTER);
}
