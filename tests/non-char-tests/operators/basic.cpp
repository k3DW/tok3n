#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("basic operators");

TEST("basic operators", "any<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, C)>, any1);
	ASSERT_PARSER_VALUES_EQ(any<static_array(B, D)>, any2);
#else
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, B, C)>, any1);
	ASSERT_PARSER_VALUES_EQ(any<static_array(B, C, D)>, any2);
#endif
	ASSERT_PARSER_VALUES_EQ(any<static_array(X, Y, Z)>, any3);
	ASSERT_PARSER_VALUES_EQ(any<static_array(B, C)>, any4);
	ASSERT_PARSER_VALUES_EQ(any<static_array(Com)>, comma);
	ASSERT_PARSER_VALUES_EQ(any<static_array(Space, Dot)>, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<(static_array<value_type, 0>{})>, any_of_parser<(static_array<value_type, 0>{})>{});
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
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, C)>, none1);
	ASSERT_PARSER_VALUES_EQ(none<static_array(B, D)>, none2);
#else
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, B, C)>, none1);
	ASSERT_PARSER_VALUES_EQ(none<static_array(B, C, D)>, none2);
#endif
	ASSERT_PARSER_VALUES_EQ(none<static_array(X, Y, Z)>, none3);
	ASSERT_PARSER_VALUES_EQ(none<static_array(B, C)>, none4);
	ASSERT_PARSER_VALUES_EQ(none<static_array(Z)>, none5);
	ASSERT_PARSER_VALUES_EQ(none<(static_array<value_type, 0>{})>, none_of_parser<(static_array<value_type, 0>{})>{});
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
	ASSERT_PARSER_VALUES_EQ(all<static_array(X, Y, Z)>, all1);
	ASSERT_PARSER_VALUES_EQ(all<static_array(Y, Z)>, all2);
	ASSERT_PARSER_VALUES_EQ(all<static_array(A, B)>, all3);
	ASSERT_PARSER_VALUES_EQ(all<static_array(Question, Question)>, qq);
	ASSERT_PARSER_VALUES_EQ(all<static_array(A, B, C)>, abc);
	ASSERT_PARSER_VALUES_EQ(all<(static_array<value_type, 0>{})>, all_of_parser<(static_array<value_type, 0>{})>{});
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
	ASSERT_PARSER_VALUES_EQ(ign<static_array(X, Y, Z)>, ignore_parser<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<static_array(Y, Z)>, ignore_parser<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<static_array(A, B)>, ignore_parser<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<static_array(Question, Question)>, ignore_parser<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<static_array(A, B, C)>, ignore_parser<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<(static_array<value_type, 0>{})>, ignore_parser<all_of_parser<(static_array<value_type, 0>{})>>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)

#if defined(__GNUC__) || defined(__clang__)
	ASSERT_PARSER_VALUES_EQ(any<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, any_of_parser<static_array(A, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, none_of_parser<static_array(A, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(X, Y, Z, A, B, C)>, any_of_parser<static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(X, Y, Z, A, B, C)>, none_of_parser<static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, B, C, X, Y, Z)>, any_of_parser<static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, B, C, X, Y, Z)>, none_of_parser<static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, X, B, Y, C, Z)>, any_of_parser<static_array(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, X, B, Y, C, Z)>, none_of_parser<static_array(B, C, X, Y, Z)>{});
#elif defined(_MSC_VER)
	ASSERT_PARSER_VALUES_EQ(any<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, any_of_parser<static_array(B, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, none_of_parser<static_array(B, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(X, Y, Z, A, B, C)>, any_of_parser<static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(X, Y, Z, A, B, C)>, none_of_parser<static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, B, C, X, Y, Z)>, any_of_parser<static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, B, C, X, Y, Z)>, none_of_parser<static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, X, B, Y, C, Z)>, any_of_parser<static_array(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, X, B, Y, C, Z)>, none_of_parser<static_array(A, C, X, Y, Z)>{});
#else
#error
#endif

#else

	ASSERT_PARSER_VALUES_EQ(any<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, any_of_parser<static_array(A, B, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>, none_of_parser<static_array(A, B, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(X, Y, Z, A, B, C)>, any_of_parser<static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(X, Y, Z, A, B, C)>, none_of_parser<static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, B, C, X, Y, Z)>, any_of_parser<static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, B, C, X, Y, Z)>, none_of_parser<static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<static_array(A, X, B, Y, C, Z)>, any_of_parser<static_array(A, B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<static_array(A, X, B, Y, C, Z)>, none_of_parser<static_array(A, B, C, X, Y, Z)>{});

#endif
}
