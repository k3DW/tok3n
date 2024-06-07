#include "pch.h"
#include "op_equals-samples/op_equals-samples.h"

using namespace SS;

FIXTURE("basic operators");

TEST("basic operators", "any<>")
{
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(A, C)>, any1);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(B, D)>, any2);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(X, Y, Z)>, any3);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(B, C)>, any4);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(Com)>, comma);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(Space, Dot)>, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<(StaticArray<S, 0>{})>, AnyOf<(StaticArray<S, 0>{})>{});
}

TEST("basic operators", "any_of<>")
{
	ASSERT_PARSER_VALUES_EQ((any_of<A, C>), any1);
	ASSERT_PARSER_VALUES_EQ((any_of<B, D>), any2);
	ASSERT_PARSER_VALUES_EQ((any_of<X, Y, Z>), any3);
	ASSERT_PARSER_VALUES_EQ((any_of<B, C>), any4);
	ASSERT_PARSER_VALUES_EQ((any_of<Com>), comma);
	ASSERT_PARSER_VALUES_EQ((any_of<Space, Dot>), spacedot);
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(A, C)>, none1);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(B, D)>, none2);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(X, Y, Z)>, none3);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(B, C)>, none4);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(Z)>, none5);
	ASSERT_PARSER_VALUES_EQ(none<(StaticArray<S, 0>{})>, NoneOf<(StaticArray<S, 0>{})>{});
}

TEST("basic operators", "none_of<>")
{
	ASSERT_PARSER_VALUES_EQ((none_of<A, C>), none1);
	ASSERT_PARSER_VALUES_EQ((none_of<B, D>), none2);
	ASSERT_PARSER_VALUES_EQ((none_of<X, Y, Z>), none3);
	ASSERT_PARSER_VALUES_EQ((none_of<B, C>), none4);
	ASSERT_PARSER_VALUES_EQ((none_of<Z>), none5);
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(X, Y, Z)>, all1);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(Y, Z)>, all2);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(A, B)>, all3);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(Question, Question)>, qq);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(A, B, C)>, abc);
	ASSERT_PARSER_VALUES_EQ(all<(StaticArray<S, 0>{})>, AllOf<(StaticArray<S, 0>{})>{});
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
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(X, Y, Z)>, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(Y, Z)>, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(A, B)>, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(Question, Question)>, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(A, B, C)>, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<(StaticArray<S, 0>{})>, Ignore<AllOf<(StaticArray<S, 0>{})>>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
#if defined(__GNUC__) || defined(__clang__)
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(B, A, C, A, C, B, A, A, B, C, C, A)>, AnyOf<StaticArray(A, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(B, A, C, A, C, B, A, A, B, C, C, A)>, NoneOf<StaticArray(A, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(X, Y, Z, A, B, C)>, AnyOf<StaticArray(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(X, Y, Z, A, B, C)>, NoneOf<StaticArray(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(A, B, C, X, Y, Z)>, AnyOf<StaticArray(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(A, B, C, X, Y, Z)>, NoneOf<StaticArray(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(A, X, B, Y, C, Z)>, AnyOf<StaticArray(B, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(A, X, B, Y, C, Z)>, NoneOf<StaticArray(B, C, X, Y, Z)>{});
#elif defined(_MSC_VER)
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(B, A, C, A, C, B, A, A, B, C, C, A)>, AnyOf<StaticArray(B, C)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(B, A, C, A, C, B, A, A, B, C, C, A)>, NoneOf<StaticArray(B, C)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(X, Y, Z, A, B, C)>, AnyOf<StaticArray(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(X, Y, Z, A, B, C)>, NoneOf<StaticArray(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(A, B, C, X, Y, Z)>, AnyOf<StaticArray(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(A, B, C, X, Y, Z)>, NoneOf<StaticArray(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(A, X, B, Y, C, Z)>, AnyOf<StaticArray(A, C, X, Y, Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(A, X, B, Y, C, Z)>, NoneOf<StaticArray(A, C, X, Y, Z)>{});
#else
#error
#endif
}
