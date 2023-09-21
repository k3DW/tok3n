#include "pch.h"

FIXTURE("not operator");

TEST("not operator", "!AnyOf")
{
	ASSERT_PARSER_VALUES_EQ(!any1, none1);
	ASSERT_PARSER_VALUES_EQ(!any2, none2);
	ASSERT_PARSER_VALUES_EQ(!any3, none3);
	ASSERT_PARSER_VALUES_EQ(!!any1, any1);
	ASSERT_PARSER_VALUES_EQ(!!any2, any2);
	ASSERT_PARSER_VALUES_EQ(!!any3, any3);
}

TEST("not operator", "!NoneOf")
{
	ASSERT_PARSER_VALUES_EQ(!none1, any1);
	ASSERT_PARSER_VALUES_EQ(!none2, any2);
	ASSERT_PARSER_VALUES_EQ(!none3, any3);
	ASSERT_PARSER_VALUES_EQ(!!none1, none1);
	ASSERT_PARSER_VALUES_EQ(!!none2, none2);
	ASSERT_PARSER_VALUES_EQ(!!none3, none3);
}



#define NOT_OPERATOR_ASSERTER(P)                                                  \
	[&]<Parser PP>(PP) {                                                          \
		if constexpr (PP::type == AnyOfType)                                      \
		{                                                                         \
			DEP_ASSERT_UNARY_OPERABLE(!, PP{}, P{});                              \
			DEP_ASSERT_PARSER_VALUES_EQ(!PP{}, NoneOf<underlying::string<PP>>{},  \
					                    !P{},  NoneOf<underlying::string<P>>{});  \
		}                                                                         \
		else if constexpr (PP::type == NoneOfType)                                \
		{                                                                         \
			DEP_ASSERT_UNARY_OPERABLE(!, PP{}, P{});                              \
			DEP_ASSERT_PARSER_VALUES_EQ(!PP{}, AnyOf<underlying::string<PP>>{},   \
					                    !P{},  AnyOf<underlying::string<P>>{});   \
		}                                                                         \
		else                                                                      \
		{                                                                         \
			DEP_ASSERT_UNARY_NOT_OPERABLE(!, PP{}, P{});                          \
		}                                                                         \
	}(P{});

TEST("not operator", "!{anything}")
{
	ASSERT_ALL_SAMPLES(NOT_OPERATOR_ASSERTER);
}
