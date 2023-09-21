#include "pch.h"

FIXTURE("not operator");

TEST("not operator", "!AnyOf")
{
	ASSERT_PARSER_VALUES_EQ(!oc1, nc1);
	ASSERT_PARSER_VALUES_EQ(!oc2, nc2);
	ASSERT_PARSER_VALUES_EQ(!oc3, nc3);
	ASSERT_PARSER_VALUES_EQ(!!oc1, oc1);
	ASSERT_PARSER_VALUES_EQ(!!oc2, oc2);
	ASSERT_PARSER_VALUES_EQ(!!oc3, oc3);
}

TEST("not operator", "!NoneOf")
{
	ASSERT_PARSER_VALUES_EQ(!nc1, oc1);
	ASSERT_PARSER_VALUES_EQ(!nc2, oc2);
	ASSERT_PARSER_VALUES_EQ(!nc3, oc3);
	ASSERT_PARSER_VALUES_EQ(!!nc1, nc1);
	ASSERT_PARSER_VALUES_EQ(!!nc2, nc2);
	ASSERT_PARSER_VALUES_EQ(!!nc3, nc3);
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
