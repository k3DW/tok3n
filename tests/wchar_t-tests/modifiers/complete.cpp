#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("complete modifier");

TEST("complete modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(com1, complete(all1));
	ASSERT_PARSER_VALUES_EQ(com2, complete(any1));
	ASSERT_PARSER_VALUES_EQ(com3, complete(all1 | any1));
	ASSERT_PARSER_VALUES_EQ(com4, complete(all1 >> any1));
	ASSERT_PARSER_VALUES_EQ(com5, complete(~(all1 >> any1)));
	ASSERT_PARSER_VALUES_EQ(com6, complete(+(all1 >> any1)));
	ASSERT_PARSER_VALUES_EQ(com7, complete(*(all1 >> any1)));
}

TEST("complete modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(com1, all1 % complete);
	ASSERT_PARSER_VALUES_EQ(com2, any1 % complete);
	ASSERT_PARSER_VALUES_EQ(com3, (all1 | any1) % complete);
	ASSERT_PARSER_VALUES_EQ(com4, (all1 >> any1) % complete);
	ASSERT_PARSER_VALUES_EQ(com5, ~(all1 >> any1) % complete);
	ASSERT_PARSER_VALUES_EQ(com6, +(all1 >> any1) % complete);
	ASSERT_PARSER_VALUES_EQ(com7, *(all1 >> any1) % complete);
}

TEST("complete modifier", "idempotent")
{
	ASSERT_PARSER_VALUES_EQ(com1, complete(com1));
	ASSERT_PARSER_VALUES_EQ(com2, complete(com2));
	ASSERT_PARSER_VALUES_EQ(com3, complete(com3));
	ASSERT_PARSER_VALUES_EQ(com4, complete(com4));
	ASSERT_PARSER_VALUES_EQ(com5, complete(com5));
	ASSERT_PARSER_VALUES_EQ(com6, complete(com6));
	ASSERT_PARSER_VALUES_EQ(com7, complete(com7));
	ASSERT_PARSER_VALUES_EQ(com1, com1 % complete);
	ASSERT_PARSER_VALUES_EQ(com2, com2 % complete);
	ASSERT_PARSER_VALUES_EQ(com3, com3 % complete);
	ASSERT_PARSER_VALUES_EQ(com4, com4 % complete);
	ASSERT_PARSER_VALUES_EQ(com5, com5 % complete);
	ASSERT_PARSER_VALUES_EQ(com6, com6 % complete);
	ASSERT_PARSER_VALUES_EQ(com7, com7 % complete);
}



#define COMPLETE_MODIFIER_ASSERTER(P)                                             \
	[&]<Parser PP>(PP) {                                                          \
		if constexpr (PP::family == CompleteFamily)                               \
		{                                                                         \
			DEP_ASSERT_MODIFIER_CALLABLE_R(complete, (PP{}), PP{},                \
				                           complete, (P{}),  P{});                \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, complete, PP{},           \
				                                  P{},  complete, P{});           \
		}                                                                         \
		else                                                                      \
		{                                                                         \
			DEP_ASSERT_MODIFIER_CALLABLE_R(complete, (PP{}), Complete<PP>{},      \
				                           complete, (P{}),  Complete<P>{});      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, complete, Complete<PP>{}, \
				                                  P{},  complete, Complete<P>{}); \
		}                                                                         \
	}(P{});

TEST("complete modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(COMPLETE_MODIFIER_ASSERTER);
}
