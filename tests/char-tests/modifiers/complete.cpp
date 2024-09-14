#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

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

TEST("complete modifier", "non consteval")
{
	(complete(any1)).parse(TT("abc"));
	(any1 % complete).parse(TT("abc"));
}



#define COMPLETE_MODIFIER_ASSERTER(P)                                                    \
	[]<parser PP>(PP) {                                                                  \
		if constexpr (PP::family == complete_family)                                     \
		{                                                                                \
			DEP_ASSERT_MODIFIER_CALLABLE_R(complete, (PP{}), PP{},                       \
				                           complete, (P{}),  P{});                       \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, complete, PP{},                  \
				                                  P{},  complete, P{});                  \
		}                                                                                \
		else                                                                             \
		{                                                                                \
			DEP_ASSERT_MODIFIER_CALLABLE_R(complete, (PP{}), complete_parser<PP>{},      \
				                           complete, (P{}),  complete_parser<P>{});      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, complete, complete_parser<PP>{}, \
				                                  P{},  complete, complete_parser<P>{}); \
		}                                                                                \
	}(P{});

TEST("complete modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(COMPLETE_MODIFIER_ASSERTER);
}
