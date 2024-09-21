#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("not operator");

TEST("not operator", "!any_of_parser")
{
	ASSERT_PARSER_VALUES_EQ(!any1, none1);
	ASSERT_PARSER_VALUES_EQ(!any2, none2);
	ASSERT_PARSER_VALUES_EQ(!any3, none3);
	ASSERT_PARSER_VALUES_EQ(!!any1, any1);
	ASSERT_PARSER_VALUES_EQ(!!any2, any2);
	ASSERT_PARSER_VALUES_EQ(!!any3, any3);
}

TEST("not operator", "!none_of_parser")
{
	ASSERT_PARSER_VALUES_EQ(!none1, any1);
	ASSERT_PARSER_VALUES_EQ(!none2, any2);
	ASSERT_PARSER_VALUES_EQ(!none3, any3);
	ASSERT_PARSER_VALUES_EQ(!!none1, none1);
	ASSERT_PARSER_VALUES_EQ(!!none2, none2);
	ASSERT_PARSER_VALUES_EQ(!!none3, none3);
}



#define NOT_OPERATOR_ASSERTER(P)                                           \
	[]<parser PP>(PP) {                                                    \
		if constexpr (PP::family == any_of_family)                         \
		{                                                                  \
			DEP_ASSERT_UNARY_OPERABLE(!, PP{}, P{});                       \
			DEP_ASSERT_PARSER_VALUES_EQ(!PP{}, none_of_parser<underlying_v<PP>>{}, \
					                    !P{},  none_of_parser<underlying_v<P>>{}); \
		}                                                                  \
		else if constexpr (PP::family == none_of_family)                   \
		{                                                                  \
			DEP_ASSERT_UNARY_OPERABLE(!, PP{}, P{});                       \
			DEP_ASSERT_PARSER_VALUES_EQ(!PP{}, any_of_parser<underlying_v<PP>>{},  \
					                    !P{},  any_of_parser<underlying_v<P>>{});  \
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
