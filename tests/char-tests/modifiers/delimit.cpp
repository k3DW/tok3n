#include "samples.h"

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

TEST("delimit modifier", "non consteval")
{
	(delimit(any1, any2)).parse(TT("abc"));
	(any1 % delimit(any2)).parse(TT("abc"));
}



#define DELIMIT_MODIFIER_ASSERTER(P)                                                                         \
	[]<Parser PP>(PP) {                                                                                      \
		DEP_ASSERT_MODIFIER_CALLABLE_R(delimit, (PP{}, comma), (Delimit<PP, Comma, std::false_type>{}),      \
			                           delimit, (P{}, comma),  (Delimit<P, Comma, std::false_type>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit(comma), (Delimit<PP, Comma, std::false_type>{}), \
			                                  P{},  delimit(comma), (Delimit<P, Comma, std::false_type>{})); \
	}(P{});

#define DELIMIT_MODIFIER_ASSERTER_2(P, D)                                                                    \
	[]<Parser PP, Parser DD>(PP, DD) {                                                                       \
		if constexpr (not std::same_as<typename PP::value_type, typename DD::value_type>)                    \
		{                                                                                                    \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(delimit, (PP{}, DD{}),                                          \
				                             delimit, (P{},  D{}));                                          \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, delimit(DD{}),                                     \
				                                    P{},  delimit(D{}));                                     \
		}                                                                                                    \
		else                                                                                                 \
		{                                                                                                    \
			DEP_ASSERT_MODIFIER_CALLABLE_R(delimit, (PP{}, DD{}), (Delimit<PP, DD, std::false_type>{}),      \
									       delimit, (P{},  D{}),  (Delimit<P, D, std::false_type>{}));       \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit(DD{}), (Delimit<PP, DD, std::false_type>{}), \
												  P{},  delimit(D{}),  (Delimit<P, D, std::false_type>{}));  \
		}                                                                                                    \
	}(P{}, D{});

#define DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
	(AnyOf<"abc">) (AnyOf<"xyz">) (AnyOf<L"abc">) (AnyOf<L"xyz">)

TEST("delimit modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(DELIMIT_MODIFIER_ASSERTER);

	ASSERT_SAMPLES_2(
		DELIMIT_MODIFIER_ASSERTER_2,
		DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES,
		DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES
	);
}
