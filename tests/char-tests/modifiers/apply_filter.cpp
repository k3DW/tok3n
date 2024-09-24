#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("apply_filter modifier");

TEST("apply_filter modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(apf1, apply_filter<filter_func3_apply>(abc >> *qq));
}

TEST("apply_filter modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(apf1, (abc >> *qq) % apply_filter<filter_func3_apply>);
}

TEST("apply_filter modifier", "non consteval")
{
	(apply_filter<true_filter>(any1 >> any2)).parse(TT("abc"));
	((any1 >> any2) % apply_filter<true_filter>).parse(TT("abc"));
}



#define APPLY_FILTER_MODIFIER_ASSERTER(P)                                                                                                   \
	[]<parser PP>(PP) {                                                                                                                     \
		DEP_ASSERT_MODIFIER_CALLABLE_R(apply_filter<true_filter>, (PP{}), (apply_filter_parser<PP, integral_constant<true_filter>>{}),      \
									   apply_filter<true_filter>, (P{}),  (apply_filter_parser<P, integral_constant<true_filter>>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, apply_filter<true_filter>, (apply_filter_parser<PP, integral_constant<true_filter>>{}), \
											  P{},  apply_filter<true_filter>, (apply_filter_parser<P, integral_constant<true_filter>>{})); \
	}(P{});

TEST("apply_filter modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(APPLY_FILTER_MODIFIER_ASSERTER);
}
