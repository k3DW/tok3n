#include "samples.h"

using namespace k3::tok3n;

FIXTURE("ignore modifier");

TEST("ignore modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(ign1, ignore(abc));
	ASSERT_PARSER_VALUES_EQ(ign2, ignore(+abc));
	ASSERT_PARSER_VALUES_EQ(ign3, ignore(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(ign4, ignore(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(ign5, ignore(+abc >> ~(abc | qq)));
}

TEST("ignore modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(ign1, abc % ignore);
	ASSERT_PARSER_VALUES_EQ(ign2, +abc % ignore);
	ASSERT_PARSER_VALUES_EQ(ign3, ~(abc | qq) % ignore);
	ASSERT_PARSER_VALUES_EQ(ign4, (abc >> *qq) % ignore);
	ASSERT_PARSER_VALUES_EQ(ign5, (+abc >> ~(abc | qq)) % ignore);
}

TEST("ignore modifier", "idempotent")
{
	ASSERT_PARSER_VALUES_EQ(ign1, ignore(ign1));
	ASSERT_PARSER_VALUES_EQ(ign2, ignore(ign2));
	ASSERT_PARSER_VALUES_EQ(ign3, ignore(ign3));
	ASSERT_PARSER_VALUES_EQ(ign4, ignore(ign4));
	ASSERT_PARSER_VALUES_EQ(ign5, ignore(ign5));
	ASSERT_PARSER_VALUES_EQ(ign1, ign1 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign2, ign2 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign3, ign3 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign4, ign4 % ignore);
	ASSERT_PARSER_VALUES_EQ(ign5, ign5 % ignore);
}

TEST("ignore modifier", "non consteval")
{
	(ignore(any1)).parse(TT("abc"));
	(any1 % ignore).parse(TT("abc"));
}



#define IGNORE_MODIFIER_ASSERTER(P)                                           \
	[]<detail::parser PP>(PP) {                                               \
		if constexpr (PP::family == detail::ignore_family)                    \
		{                                                                     \
			DEP_ASSERT_MODIFIER_CALLABLE_R(ignore, (PP{}), PP{},              \
				                           ignore, (P{}),  P{});              \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, ignore, PP{},         \
				                                  P{},  ignore, P{});         \
		}                                                                     \
		else                                                                  \
		{                                                                     \
			DEP_ASSERT_MODIFIER_CALLABLE_R(ignore, (PP{}), Ignore<PP>{},      \
				                           ignore, (P{}),  Ignore<P>{});      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, ignore, Ignore<PP>{}, \
				                                  P{},  ignore, Ignore<P>{}); \
		}                                                                     \
	}(P{});

TEST("ignore modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(IGNORE_MODIFIER_ASSERTER);
}
