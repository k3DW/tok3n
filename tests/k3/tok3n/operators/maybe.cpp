#include "pch.h"

FIXTURE("maybe operator");

TEST("maybe operator", "~Maybe")
{
	ASSERT_PARSER_VALUES_EQ(~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~~may4, may4);
}

TEST("maybe operator", "~OneOrMore")
{
	ASSERT_PARSER_VALUES_EQ(~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~oom4, zom4);
}

TEST("maybe operator", "~ZeroOrMore")
{
	ASSERT_PARSER_VALUES_EQ(~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~zom4, zom4);
}



#define MAYBE_OPERATOR_ASSERTER(P)                                                       \
	[&]<Parser PP>(PP) {                                                                 \
		if constexpr (std::same_as<typename PP::result_type, void>)                      \
		{                                                                                \
			DEP_ASSERT_UNARY_NOT_OPERABLE(~, PP{}, P{});                                 \
		}                                                                                \
		else                                                                             \
		{                                                                                \
			DEP_ASSERT_UNARY_OPERABLE(~, PP{}, P{});                                     \
			if constexpr (PP::type == MaybeFamily)                                       \
			{                                                                            \
				DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, PP{},                                 \
					                        ~P{},  P{});                                 \
			}                                                                            \
			else if constexpr (PP::type == OneOrMoreFamily)                              \
			{                                                                            \
				DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, ZeroOrMore<underlying::parser<PP>>{}, \
				                            ~P{},  ZeroOrMore<underlying::parser<P>>{}); \
			}                                                                            \
			else if constexpr (PP::type == ZeroOrMoreFamily)                             \
			{                                                                            \
				DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, PP{},                                 \
				                            ~P{},  P{});                                 \
			}                                                                            \
			else                                                                         \
			{                                                                            \
				DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, Maybe<PP>{},                          \
				                            ~P{},  Maybe<P>{});                          \
			}                                                                            \
		}                                                                                \
	}(P{});

TEST("maybe operator", "~{anything}")
{
	ASSERT_ALL_SAMPLES(MAYBE_OPERATOR_ASSERTER);
}
