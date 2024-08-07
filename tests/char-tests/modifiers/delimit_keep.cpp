#include "samples.h"

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

TEST("delimit_keep modifier", "non consteval")
{
	(delimit_keep(any1, any2)).parse(TT("abc"));
	(any1 % delimit_keep(any2)).parse(TT("abc"));
}



#define DELIMIT_KEEP_MODIFIER_ASSERTER(P)                                                              \
	[]<Parser PP>(PP) {                                                                                \
		DEP_ASSERT_MODIFIER_CALLABLE_R(delimit_keep, (PP{}, comma), (Delimit<PP, Comma, True>{}),      \
			                           delimit_keep, (P{}, comma),  (Delimit<P, Comma, True>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit_keep(comma), (Delimit<PP, Comma, True>{}), \
			                                  P{},  delimit_keep(comma), (Delimit<P, Comma, True>{})); \
	}(P{});

#define DELIMIT_KEEP_MODIFIER_ASSERTER_2(P, D)                                                         \
	[]<Parser PP, Parser DD>(PP, DD) {                                                                 \
		if constexpr (not std::same_as<typename PP::value_type, typename DD::value_type>)              \
		{                                                                                              \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(delimit_keep, (PP{}, DD{}),                               \
				                             delimit_keep, (P{},  D{}));                               \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, delimit_keep(DD{}),                          \
				                                    P{},  delimit_keep(D{}));                          \
		}                                                                                              \
		else                                                                                           \
		{                                                                                              \
			DEP_ASSERT_MODIFIER_CALLABLE_R(delimit_keep, (PP{}, DD{}), (Delimit<PP, DD, True>{}),      \
									       delimit_keep, (P{},  D{}),  (Delimit<P, D, True>{}));       \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit_keep(DD{}), (Delimit<PP, DD, True>{}), \
												  P{},  delimit_keep(D{}),  (Delimit<P, D, True>{}));  \
		}                                                                                              \
	}(P{}, D{});

#define DELIMIT_KEEP_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
	(AnyOf<"abc">) (AnyOf<"xyz">) (AnyOf<L"abc">) (AnyOf<L"xyz">)

TEST("delimit_keep modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(DELIMIT_KEEP_MODIFIER_ASSERTER);

	ASSERT_SAMPLES_2(
		DELIMIT_KEEP_MODIFIER_ASSERTER_2,
		DELIMIT_KEEP_SAMPLES_LIST_DIFFERENT_VALUE_TYPES,
		DELIMIT_KEEP_SAMPLES_LIST_DIFFERENT_VALUE_TYPES
	);
}
