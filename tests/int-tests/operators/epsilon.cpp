#include "pch.h"
#include "int-tests/samples.h"

FIXTURE("epsilon operator");

namespace {

template <auto lhs, auto rhs>
concept choice_operable = requires { lhs | rhs; };

} // namespace

TEST("epsilon operator", ".of<>")
{
	ASSERT_PARSER_VALUES_EQ(eps.of<value_type>, Epsilon<value_type>{});
}

TEST("epsilon operator", "P | eps")
{
	ASSERT_PARSER_VALUES_EQ(any1 | eps, (Choice<Any1, Epsilon<value_type>>{}));
	ASSERT_PARSER_VALUES_EQ(any2 | eps, (Choice<Any2, Epsilon<value_type>>{}));
	ASSERT_PARSER_VALUES_EQ(any3 | eps, (Choice<Any3, Epsilon<value_type>>{}));
}

TEST("epsilon operator", "eps | P")
{
	ASSERT((not choice_operable<eps, any1>), "The expression `eps | any1` compiled, but it should not");
	ASSERT((not choice_operable<eps, any2>), "The expression `eps | any2` compiled, but it should not");
	ASSERT((not choice_operable<eps, any3>), "The expression `eps | any3` compiled, but it should not");
}
