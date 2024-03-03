#include "pch.h"
#include "enum-samples/enum-samples.h"

FIXTURE("basic operators");

TEST("basic operators", "any<>")
{
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::A, E::B, E::C)>, any1);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::B, E::C, E::D)>, any2);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::X, E::Y, E::Z)>, any3);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::C, E::D)>, any4);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::Com)>, comma);
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::Space, E::Dot)>, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<(StaticArray<E, 0>{})>, AnyOf<(StaticArray<E, 0>{})>{});
	ASSERT_PARSER_VALUES_EQ(any<(StaticArray<E, 0>{})>, nothing<E>);
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::A, E::B, E::C)>, none1);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::B, E::C, E::D)>, none2);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::X, E::Y, E::Z)>, none3);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::C, E::D)>, none4);
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::Z)>, none5);
	ASSERT_PARSER_VALUES_EQ(none<(StaticArray<E, 0>{})>, NoneOf<(StaticArray<E, 0>{})>{});
	ASSERT_PARSER_VALUES_EQ(none<(StaticArray<E, 0>{})>, anything<E>);
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(E::X, E::Y, E::Z)>, all1);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(E::Y, E::Z)>, all2);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(E::A, E::B)>, all3);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(E::Question, E::Question)>, qq);
	ASSERT_PARSER_VALUES_EQ(all<StaticArray(E::A, E::B, E::C)>, abc);
	ASSERT_PARSER_VALUES_EQ(all<(StaticArray<E, 0>{})>, AllOf<(StaticArray<E, 0>{})>{});
	ASSERT_PARSER_VALUES_EQ(all<(StaticArray<E, 0>{})>, eps<E>);
}

TEST("basic operators", "ign<>")
{
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(E::X, E::Y, E::Z)>, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(E::Y, E::Z)>, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(E::A, E::B)>, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(E::Question, E::Question)>, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<StaticArray(E::A, E::B, E::C)>, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<(StaticArray<E, 0>{})>, Ignore<AllOf<(StaticArray<E, 0>{})>>{});
	ASSERT_PARSER_VALUES_EQ(ign<(StaticArray<E, 0>{})>, Ignore<std::remove_const_t<decltype(eps<E>)>>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::B, E::A, E::C, E::A, E::C, E::B, E::A, E::A, E::B, E::C, E::C, E::A)>, AnyOf<StaticArray(E::A, E::B, E::C)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::B, E::A, E::C, E::A, E::C, E::B, E::A, E::A, E::B, E::C, E::C, E::A)>, NoneOf<StaticArray(E::A, E::B, E::C)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::X, E::Y, E::Z, E::A, E::B, E::C)>, AnyOf<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::X, E::Y, E::Z, E::A, E::B, E::C)>, NoneOf<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>, AnyOf<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>, NoneOf<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>{});
	ASSERT_PARSER_VALUES_EQ(any<StaticArray(E::A, E::X, E::B, E::Y, E::C, E::Z)>, AnyOf<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>{});
	ASSERT_PARSER_VALUES_EQ(none<StaticArray(E::A, E::X, E::B, E::Y, E::C, E::Z)>, NoneOf<StaticArray(E::A, E::B, E::C, E::X, E::Y, E::Z)>{});
}
