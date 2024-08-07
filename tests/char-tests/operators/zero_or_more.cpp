#include "samples.h"

FIXTURE("zero_or_more operator");

TEST("zero_or_more operator", "*Maybe")
{
	ASSERT_PARSER_VALUES_EQ(*may1, zom1);
	ASSERT_PARSER_VALUES_EQ(**may1, zom1);
	ASSERT_PARSER_VALUES_EQ(***may1, zom1);
	ASSERT_PARSER_VALUES_EQ(*may2, zom2);
	ASSERT_PARSER_VALUES_EQ(**may2, zom2);
	ASSERT_PARSER_VALUES_EQ(***may2, zom2);
	ASSERT_PARSER_VALUES_EQ(*may3, zom3);
	ASSERT_PARSER_VALUES_EQ(**may3, zom3);
	ASSERT_PARSER_VALUES_EQ(***may3, zom3);
	ASSERT_PARSER_VALUES_EQ(*may4, zom4);
	ASSERT_PARSER_VALUES_EQ(**may4, zom4);
	ASSERT_PARSER_VALUES_EQ(***may4, zom4);
}

TEST("zero_or_more operator", "*OneOrMore")
{
	ASSERT_PARSER_VALUES_EQ(*oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(**oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(***oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(*oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(**oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(***oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(*oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(**oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(***oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(*oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(**oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(***oom4, zom4);
}

TEST("zero_or_more operator", "*ZeroOrMore")
{
	ASSERT_PARSER_VALUES_EQ(*zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(**zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(***zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(*zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(**zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(***zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(*zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(**zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(***zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(*zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(**zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(***zom4, zom4);
}

TEST("zero_or_more operator", "non consteval")
{
	(*any1).parse(TT("abc"));
}



#define ZERO_OR_MORE_OPERATOR_ASSERTER(P)                                      \
	[]<Parser PP>(PP) {                                                        \
		DEP_ASSERT_UNARY_OPERABLE(*, PP{}, P{});                               \
		if constexpr (PP::family == MaybeFamily)                               \
		{                                                                      \
			DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, ZeroOrMore<underlying_t<PP>>{}, \
										*P{},  ZeroOrMore<underlying_t<P>>{}); \
		}                                                                      \
		else if constexpr (PP::family == OneOrMoreFamily)                      \
		{                                                                      \
			DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, ZeroOrMore<underlying_t<PP>>{}, \
										*P{},  ZeroOrMore<underlying_t<P>>{}); \
		}                                                                      \
		else if constexpr (PP::family == ZeroOrMoreFamily)                     \
		{                                                                      \
			DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, PP{},                           \
										*P{},  P{});                           \
		}                                                                      \
		else                                                                   \
		{                                                                      \
			DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, ZeroOrMore<PP>{},               \
										*P{},  ZeroOrMore<P>{});               \
		}                                                                      \
	}(P{});

TEST("zero_or_more operator", "*{anything}")
{
	ASSERT_ALL_SAMPLES(ZERO_OR_MORE_OPERATOR_ASSERTER);
}
