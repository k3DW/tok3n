#include "samples.h"

using namespace k3::tok3n;

FIXTURE("map modifier");

TEST("map modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(tra1, map<func1>(+abc));
	ASSERT_PARSER_VALUES_EQ(tra2, map<func2>(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(tra3, map<func3>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(tra4, map<func4(3)>(+abc >> ~(abc | qq)));
	ASSERT_PARSER_VALUES_NE(tra4, map<func4(2)>(+abc >> ~(abc | qq)));
}

TEST("map modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(tra1, +abc % map<func1>);
	ASSERT_PARSER_VALUES_EQ(tra2, ~(abc | qq) % map<func2>);
	ASSERT_PARSER_VALUES_EQ(tra3, (abc >> *qq) % map<func3>);
	ASSERT_PARSER_VALUES_EQ(tra4, (+abc >> ~(abc | qq)) % map<func4(3)>);
	ASSERT_PARSER_VALUES_NE(tra4, (+abc >> ~(abc | qq)) % map<func4(2)>);
}

TEST("map modifier", "non consteval")
{
	constexpr auto sink = [](auto&&) {};
	(map<sink>(any1)).parse(TT("abc"));
	(any1 % map<sink>).parse(TT("abc"));
}



#define FN_MODIFIER_ASSERTER(P)                                                                                        \
	[]<detail::parser PP>(PP) {                                                                                        \
		DEP_ASSERT_MODIFIER_CALLABLE_R(map<sink_func>, (PP{}), (Map<PP, detail::integral_constant<sink_func>>{}),      \
			                           map<sink_func>, (P{}),  (Map<P, detail::integral_constant<sink_func>>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, map<sink_func>, (Map<PP, detail::integral_constant<sink_func>>{}), \
			                                  P{},  map<sink_func>, (Map<P, detail::integral_constant<sink_func>>{})); \
	}(P{});

TEST("map modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(FN_MODIFIER_ASSERTER);
}
