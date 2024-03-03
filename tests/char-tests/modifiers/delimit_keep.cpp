#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("delimit_keep modifier");

TEST("delimit_keep modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(dek1, delimit_keep(abc, comma));
	ASSERT_PARSER_VALUES_EQ(dek2, delimit_keep(abc, spacedot));
	ASSERT_PARSER_VALUES_EQ(dek3, delimit_keep(qq, comma));
	ASSERT_PARSER_VALUES_EQ(dek4, delimit_keep(qq, spacedot));
	ASSERT_PARSER_VALUES_EQ(dek5, delimit_keep(comma, abc));
	ASSERT_PARSER_VALUES_EQ(dek6, delimit_keep(spacedot, abc));
	ASSERT_PARSER_VALUES_EQ(dek7, delimit_keep(comma, qq));
	ASSERT_PARSER_VALUES_EQ(dek8, delimit_keep(spacedot, qq));
}

TEST("delimit_keep modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(dek1, abc % delimit_keep(comma));
	ASSERT_PARSER_VALUES_EQ(dek2, abc % delimit_keep(spacedot));
	ASSERT_PARSER_VALUES_EQ(dek3, qq % delimit_keep(comma));
	ASSERT_PARSER_VALUES_EQ(dek4, qq % delimit_keep(spacedot));
	ASSERT_PARSER_VALUES_EQ(dek5, comma % delimit_keep(abc));
	ASSERT_PARSER_VALUES_EQ(dek6, spacedot % delimit_keep(abc));
	ASSERT_PARSER_VALUES_EQ(dek7, comma % delimit_keep(qq));
	ASSERT_PARSER_VALUES_EQ(dek8, spacedot % delimit_keep(qq));
}



#define DELIMIT_KEEP_MODIFIER_ASSERTER(P)                                                                  \
	[&]<Parser PP>(PP) {                                                                                   \
		ASSERT_MODIFIER_NOT_CALLABLE(delimit_keep, (P{}, ignore(comma)));                                  \
		ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P{}, delimit_keep(ignore(comma)));                             \
		if constexpr (std::same_as<typename PP::result_type, void>)                                        \
		{                                                                                                  \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(delimit_keep, (PP{}, comma),                                  \
				                             delimit_keep, (P{}, comma));                                  \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, delimit_keep(comma),                             \
				                                    P{},  delimit_keep(comma));                            \
		}                                                                                                  \
		else                                                                                               \
		{                                                                                                  \
			DEP_ASSERT_MODIFIER_CALLABLE_R(delimit_keep, (PP{}, comma), (Delimit<PP, Comma, True>{}),      \
				                           delimit_keep, (P{}, comma),  (Delimit<P, Comma, True>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit_keep(comma), (Delimit<PP, Comma, True>{}), \
				                                  P{},  delimit_keep(comma), (Delimit<P, Comma, True>{})); \
		}                                                                                                  \
	}(P{});

TEST("delimit_keep modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(DELIMIT_KEEP_MODIFIER_ASSERTER);
}
