#include "samples.h"

using namespace k3::tok3n;

FIXTURE("apply modifier");

TEST("apply modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(apm1, apply<func3_apply>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(apm2, apply<func4_apply(3)>(+abc >> ~(abc | qq)));
	ASSERT_PARSER_VALUES_NE(apm2, apply<func4_apply(2)>(+abc >> ~(abc | qq)));
}

TEST("apply modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(apm1, (abc >> *qq) % apply<func3_apply>);
	ASSERT_PARSER_VALUES_EQ(apm2, (+abc >> ~(abc | qq)) % apply<func4_apply(3)>);
	ASSERT_PARSER_VALUES_NE(apm2, (+abc >> ~(abc | qq)) % apply<func4_apply(2)>);
}

TEST("apply modifier", "non consteval")
{
	constexpr auto sink = [](auto&&...) {};
	(apply<sink>(any1 >> any2)).parse(TT("abc"));
	((any1 >> any2) % apply<sink>).parse(TT("abc"));
}



#define APPLY_MODIFIER_ASSERTER(P)                                                                                                     \
	[]<detail::parser PP>(PP) {                                                                                                        \
		DEP_ASSERT_MODIFIER_CALLABLE_R(apply<sink_func>, (PP{}), (aliases::ApplyMap<PP, detail::integral_constant<sink_func>>{}),      \
									   apply<sink_func>, (P{}),  (aliases::ApplyMap<P, detail::integral_constant<sink_func>>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, apply<sink_func>, (aliases::ApplyMap<PP, detail::integral_constant<sink_func>>{}), \
											  P{},  apply<sink_func>, (aliases::ApplyMap<P, detail::integral_constant<sink_func>>{})); \
	}(P{});

TEST("apply modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(APPLY_MODIFIER_ASSERTER);
}
