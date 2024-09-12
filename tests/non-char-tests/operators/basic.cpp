#include "samples.h"

FIXTURE("basic operators");

TEST("basic operators", "any<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, C)>, any1);
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(B, D)>, any2);
#else
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, B, C)>, any1);
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(B, C, D)>, any2);
#endif
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(X, Y, Z)>, any3);
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(B, C)>, any4);
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(Com)>, comma);
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(Space, Dot)>, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<(detail::static_array<value_type, 0>{})>, AnyOf<(detail::static_array<value_type, 0>{})>{});
}

TEST("basic operators", "any_of<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSER_VALUES_EQ((any_of<A, C>), any1);
	ASSERT_PARSER_VALUES_EQ((any_of<B, D>), any2);
#else
	ASSERT_PARSER_VALUES_EQ((any_of<A, B, C>), any1);
	ASSERT_PARSER_VALUES_EQ((any_of<B, C, D>), any2);
#endif
	ASSERT_PARSER_VALUES_EQ((any_of<X, Y, Z>), any3);
	ASSERT_PARSER_VALUES_EQ((any_of<B, C>), any4);
	ASSERT_PARSER_VALUES_EQ((any_of<Com>), comma);
	ASSERT_PARSER_VALUES_EQ((any_of<Space, Dot>), spacedot);
}

TEST("basic operators", "none<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, C)>, none1);
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(B, D)>, none2);
#else
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, B, C)>, none1);
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(B, C, D)>, none2);
#endif
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(X, Y, Z)>, none3);
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(B, C)>, none4);
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(Z)>, none5);
	ASSERT_PARSER_VALUES_EQ(none<(detail::static_array<value_type, 0>{})>, NoneOf<(detail::static_array<value_type, 0>{})>{});
}

TEST("basic operators", "none_of<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSER_VALUES_EQ((none_of<A, C>), none1);
	ASSERT_PARSER_VALUES_EQ((none_of<B, D>), none2);
#else
	ASSERT_PARSER_VALUES_EQ((none_of<A, B, C>), none1);
	ASSERT_PARSER_VALUES_EQ((none_of<B, C, D>), none2);
#endif
	ASSERT_PARSER_VALUES_EQ((none_of<X, Y, Z>), none3);
	ASSERT_PARSER_VALUES_EQ((none_of<B, C>), none4);
	ASSERT_PARSER_VALUES_EQ((none_of<Z>), none5);
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<detail::static_array(X, Y, Z)>, all1);
	ASSERT_PARSER_VALUES_EQ(all<detail::static_array(Y, Z)>, all2);
	ASSERT_PARSER_VALUES_EQ(all<detail::static_array(A, B)>, all3);
	ASSERT_PARSER_VALUES_EQ(all<detail::static_array(Question, Question)>, qq);
	ASSERT_PARSER_VALUES_EQ(all<detail::static_array(A, B, C)>, abc);
	ASSERT_PARSER_VALUES_EQ(all<(detail::static_array<value_type, 0>{})>, AllOf<(detail::static_array<value_type, 0>{})>{});
}

TEST("basic operators", "all_of<>")
{
	ASSERT_PARSER_VALUES_EQ((all_of<X, Y, Z>), all1);
	ASSERT_PARSER_VALUES_EQ((all_of<Y, Z>), all2);
	ASSERT_PARSER_VALUES_EQ((all_of<A, B>), all3);
	ASSERT_PARSER_VALUES_EQ((all_of<Question, Question>), qq);
	ASSERT_PARSER_VALUES_EQ((all_of<A, B, C>), abc);
}

TEST("basic operators", "ign<>")
{
	ASSERT_PARSER_VALUES_EQ(ign<detail::static_array(X, Y, Z)>, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<detail::static_array(Y, Z)>, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<detail::static_array(A, B)>, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<detail::static_array(Question, Question)>, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<detail::static_array(A, B, C)>, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<(detail::static_array<value_type, 0>{})>, Ignore<AllOf<(detail::static_array<value_type, 0>{})>>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)

#if defined(__GNUC__) || defined(__clang__)
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, AnyOf<detail::static_array(A, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, NoneOf<detail::static_array(A, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(X, Y, Z, A, B, C)>, AnyOf<detail::static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(X, Y, Z, A, B, C)>, NoneOf<detail::static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, B, C, X, Y, Z)>, AnyOf<detail::static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, B, C, X, Y, Z)>, NoneOf<detail::static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, X, B, Y, C, Z)>, AnyOf<detail::static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, X, B, Y, C, Z)>, NoneOf<detail::static_array(B, C, X, Y, Z)>{});
#elif defined(_MSC_VER)
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, AnyOf<detail::static_array(B, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, NoneOf<detail::static_array(B, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(X, Y, Z, A, B, C)>, AnyOf<detail::static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(X, Y, Z, A, B, C)>, NoneOf<detail::static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, B, C, X, Y, Z)>, AnyOf<detail::static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, B, C, X, Y, Z)>, NoneOf<detail::static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, X, B, Y, C, Z)>, AnyOf<detail::static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, X, B, Y, C, Z)>, NoneOf<detail::static_array(A, C, X, Y, Z)>{});
#else
#error
#endif

#else

	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, AnyOf<detail::static_array(A, B, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, NoneOf<detail::static_array(A, B, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(X, Y, Z, A, B, C)>, AnyOf<detail::static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(X, Y, Z, A, B, C)>, NoneOf<detail::static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, B, C, X, Y, Z)>, AnyOf<detail::static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, B, C, X, Y, Z)>, NoneOf<detail::static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<detail::static_array(A, X, B, Y, C, Z)>, AnyOf<detail::static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<detail::static_array(A, X, B, Y, C, Z)>, NoneOf<detail::static_array(A, B, C, X, Y, Z)>{});

#endif
}
