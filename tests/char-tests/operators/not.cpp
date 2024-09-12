#include "samples.h"

using namespace k3::tok3n;

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

TEST("not operator", "non consteval")
{
	(!any1).parse(TT("abc"));
}



#define NOT_OPERATOR_ASSERTER(P)                                           \
	[]<detail::parser PP>(PP) {                                            \
		if constexpr (PP::family == detail::any_of_family)                 \
		{                                                                  \
			DEP_ASSERT_UNARY_OPERABLE(!, PP{}, P{});                       \
			DEP_ASSERT_PARSER_VALUES_EQ(!PP{}, NoneOf<underlying_v<PP>>{}, \
					                    !P{},  NoneOf<underlying_v<P>>{}); \
		}                                                                  \
		else if constexpr (PP::family == detail::none_of_family)           \
		{                                                                  \
			DEP_ASSERT_UNARY_OPERABLE(!, PP{}, P{});                       \
			DEP_ASSERT_PARSER_VALUES_EQ(!PP{}, AnyOf<underlying_v<PP>>{},  \
					                    !P{},  AnyOf<underlying_v<P>>{});  \
		}                                                                  \
		else                                                               \
		{                                                                  \
			DEP_ASSERT_UNARY_NOT_OPERABLE(!, PP{}, P{});                   \
		}                                                                  \
	}(P{});

TEST("not operator", "!{anything}")
{
	ASSERT_ALL_SAMPLES(NOT_OPERATOR_ASSERTER);
}
