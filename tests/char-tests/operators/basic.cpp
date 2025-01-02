// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("basic operators");

TEST("basic operators", "UDL _any")
{
	ASSERT_PARSER_VALUES_EQ(TT("abc"_any), any1);
	ASSERT_PARSER_VALUES_EQ(TT("bcd"_any), any2);
	ASSERT_PARSER_VALUES_EQ(TT("xyz"_any), any3);
	ASSERT_PARSER_VALUES_EQ(TT("cd"_any), any4);
	ASSERT_PARSER_VALUES_EQ(TT(","_any), comma);
	ASSERT_PARSER_VALUES_EQ(TT(" ."_any), spacedot);
	ASSERT_PARSER_VALUES_EQ(TT(""_any), any_of_parser<TT("")>{});
}

TEST("basic operators", "UDL _any_of")
{
	ASSERT_PARSER_VALUES_EQ(TT("abc"_any_of), any1);
	ASSERT_PARSER_VALUES_EQ(TT("bcd"_any_of), any2);
	ASSERT_PARSER_VALUES_EQ(TT("xyz"_any_of), any3);
	ASSERT_PARSER_VALUES_EQ(TT("cd"_any_of), any4);
	ASSERT_PARSER_VALUES_EQ(TT(","_any_of), comma);
	ASSERT_PARSER_VALUES_EQ(TT(" ."_any_of), spacedot);
	ASSERT_PARSER_VALUES_EQ(TT(""_any_of), any_of_parser<TT("")>{});
}

TEST("basic operators", "any<>")
{
	ASSERT_PARSER_VALUES_EQ(any<TT("abc")>, any1);
	ASSERT_PARSER_VALUES_EQ(any<TT("bcd")>, any2);
	ASSERT_PARSER_VALUES_EQ(any<TT("xyz")>, any3);
	ASSERT_PARSER_VALUES_EQ(any<TT("cd")>, any4);
	ASSERT_PARSER_VALUES_EQ(any<TT(",")>, comma);
	ASSERT_PARSER_VALUES_EQ(any<TT(" .")>, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<TT("")>, any_of_parser<TT("")>{});
}

TEST("basic operators", "any_of<>")
{
	ASSERT_PARSER_VALUES_EQ((any_of<TT('a'), TT('b'), TT('c')>), any1);
	ASSERT_PARSER_VALUES_EQ((any_of<TT('b'), TT('c'), TT('d')>), any2);
	ASSERT_PARSER_VALUES_EQ((any_of<TT('x'), TT('y'), TT('z')>), any3);
	ASSERT_PARSER_VALUES_EQ((any_of<TT('c'), TT('d')>), any4);
	ASSERT_PARSER_VALUES_EQ((any_of<TT(',')>), comma);
	ASSERT_PARSER_VALUES_EQ((any_of<TT(' '), TT('.')>), spacedot);
}

TEST("basic operators", "UDL _none")
{
	ASSERT_PARSER_VALUES_EQ(TT("abc"_none), none1);
	ASSERT_PARSER_VALUES_EQ(TT("bcd"_none), none2);
	ASSERT_PARSER_VALUES_EQ(TT("xyz"_none), none3);
	ASSERT_PARSER_VALUES_EQ(TT("cd"_none), none4);
	ASSERT_PARSER_VALUES_EQ(TT("z"_none), none5);
	ASSERT_PARSER_VALUES_EQ(TT(""_none), none_of_parser<TT("")>{});
}

TEST("basic operators", "UDL _none_of")
{
	ASSERT_PARSER_VALUES_EQ(TT("abc"_none_of), none1);
	ASSERT_PARSER_VALUES_EQ(TT("bcd"_none_of), none2);
	ASSERT_PARSER_VALUES_EQ(TT("xyz"_none_of), none3);
	ASSERT_PARSER_VALUES_EQ(TT("cd"_none_of), none4);
	ASSERT_PARSER_VALUES_EQ(TT("z"_none_of), none5);
	ASSERT_PARSER_VALUES_EQ(TT(""_none_of), none_of_parser<TT("")>{});
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<TT("abc")>, none1);
	ASSERT_PARSER_VALUES_EQ(none<TT("bcd")>, none2);
	ASSERT_PARSER_VALUES_EQ(none<TT("xyz")>, none3);
	ASSERT_PARSER_VALUES_EQ(none<TT("cd")>, none4);
	ASSERT_PARSER_VALUES_EQ(none<TT("z")>, none5);
	ASSERT_PARSER_VALUES_EQ(none<TT("")>, none_of_parser<TT("")>{});
}

TEST("basic operators", "none_of<>")
{
	ASSERT_PARSER_VALUES_EQ((none_of<TT('a'), TT('b'), TT('c')>), none1);
	ASSERT_PARSER_VALUES_EQ((none_of<TT('b'), TT('c'), TT('d')>), none2);
	ASSERT_PARSER_VALUES_EQ((none_of<TT('x'), TT('y'), TT('z')>), none3);
	ASSERT_PARSER_VALUES_EQ((none_of<TT('c'), TT('d')>), none4);
	ASSERT_PARSER_VALUES_EQ((none_of<TT('z')>), none5);
}

TEST("basic operators", "UDL _all")
{
	ASSERT_PARSER_VALUES_EQ(TT("literal"_all), all1);
	ASSERT_PARSER_VALUES_EQ(TT("ly"_all), all2);
	ASSERT_PARSER_VALUES_EQ(TT("test"_all), all3);
	ASSERT_PARSER_VALUES_EQ(TT("ab"_all), all4);
	ASSERT_PARSER_VALUES_EQ(TT("??"_all), qq);
	ASSERT_PARSER_VALUES_EQ(TT("abc"_all), abc);
	ASSERT_PARSER_VALUES_EQ(TT(""_all), all_of_parser<TT("")>{});
}

TEST("basic operators", "UDL _all_of")
{
	ASSERT_PARSER_VALUES_EQ(TT("literal"_all_of), all1);
	ASSERT_PARSER_VALUES_EQ(TT("ly"_all_of), all2);
	ASSERT_PARSER_VALUES_EQ(TT("test"_all_of), all3);
	ASSERT_PARSER_VALUES_EQ(TT("ab"_all_of), all4);
	ASSERT_PARSER_VALUES_EQ(TT("??"_all_of), qq);
	ASSERT_PARSER_VALUES_EQ(TT("abc"_all_of), abc);
	ASSERT_PARSER_VALUES_EQ(TT(""_all_of), all_of_parser<TT("")>{});
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<TT("literal")>, all1);
	ASSERT_PARSER_VALUES_EQ(all<TT("ly")>, all2);
	ASSERT_PARSER_VALUES_EQ(all<TT("test")>, all3);
	ASSERT_PARSER_VALUES_EQ(all<TT("ab")>, all4);
	ASSERT_PARSER_VALUES_EQ(all<TT("??")>, qq);
	ASSERT_PARSER_VALUES_EQ(all<TT("abc")>, abc);
	ASSERT_PARSER_VALUES_EQ(all<TT("")>, all_of_parser<TT("")>{});
}

TEST("basic operators", "all_of<>")
{
	ASSERT_PARSER_VALUES_EQ((all_of<TT('l'), TT('i'), TT('t'), TT('e'), TT('r'), TT('a'), TT('l')>), all1);
	ASSERT_PARSER_VALUES_EQ((all_of<TT('l'), TT('y')>), all2);
	ASSERT_PARSER_VALUES_EQ((all_of<TT('t'), TT('e'), TT('s'), TT('t')>), all3);
	ASSERT_PARSER_VALUES_EQ((all_of<TT('a'), TT('b')>), all4);
	ASSERT_PARSER_VALUES_EQ((all_of<TT('?'), TT('?')>), qq);
	ASSERT_PARSER_VALUES_EQ((all_of<TT('a'), TT('b'), TT('c')>), abc);
}

TEST("basic operators", "UDL _ign")
{
	ASSERT_PARSER_VALUES_EQ(TT("literal"_ign), ignore_parser<All1>{});
	ASSERT_PARSER_VALUES_EQ(TT("ly"_ign), ignore_parser<All2>{});
	ASSERT_PARSER_VALUES_EQ(TT("test"_ign), ignore_parser<All3>{});
	ASSERT_PARSER_VALUES_EQ(TT("ab"_ign), ignore_parser<All4>{});
	ASSERT_PARSER_VALUES_EQ(TT("??"_ign), ignore_parser<QQ>{});
	ASSERT_PARSER_VALUES_EQ(TT("abc"_ign), ignore_parser<ABC>{});
	ASSERT_PARSER_VALUES_EQ(TT(""_ign), ignore_parser<all_of_parser<TT("")>>{});
}

TEST("basic operators", "ign<>")
{
	ASSERT_PARSER_VALUES_EQ(ign<TT("literal")>, ignore_parser<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<TT("ly")>, ignore_parser<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<TT("test")>, ignore_parser<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<TT("ab")>, ignore_parser<All4>{});
	ASSERT_PARSER_VALUES_EQ(ign<TT("??")>, ignore_parser<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<TT("abc")>, ignore_parser<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<TT("")>, ignore_parser<all_of_parser<TT("")>>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
	ASSERT_PARSER_VALUES_EQ(TT("212312323321212311"_any), any_of_parser<TT("123")>{});
	ASSERT_PARSER_VALUES_EQ(TT("212312323321212311"_none), none_of_parser<TT("123")>{});
	ASSERT_PARSER_VALUES_EQ(TT("123abc"_any), any_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("123abc"_none), none_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("abc123"_any), any_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("abc123"_none), none_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("a1b2c3"_any), any_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("a1b2c3"_none), none_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("Aa"_any), any_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("Aa"_none), none_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("aA"_any), any_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("aA"_none), none_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("A"_any), any_of_parser<TT("A")>{});
	ASSERT_PARSER_VALUES_EQ(TT("A"_none), none_of_parser<TT("A")>{});
	ASSERT_PARSER_VALUES_EQ(TT(""_any), any_of_parser<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(TT(""_none), none_of_parser<TT("")>{});

	ASSERT_PARSER_VALUES_EQ(TT("212312323321212311"_any_of), any_of_parser<TT("123")>{});
	ASSERT_PARSER_VALUES_EQ(TT("212312323321212311"_none_of), none_of_parser<TT("123")>{});
	ASSERT_PARSER_VALUES_EQ(TT("123abc"_any_of), any_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("123abc"_none_of), none_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("abc123"_any_of), any_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("abc123"_none_of), none_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("a1b2c3"_any_of), any_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("a1b2c3"_none_of), none_of_parser<TT("123abc")>{});
	ASSERT_PARSER_VALUES_EQ(TT("Aa"_any_of), any_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("Aa"_none_of), none_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("aA"_any_of), any_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("aA"_none_of), none_of_parser<TT("Aa")>{});
	ASSERT_PARSER_VALUES_EQ(TT("A"_any_of), any_of_parser<TT("A")>{});
	ASSERT_PARSER_VALUES_EQ(TT("A"_none_of), none_of_parser<TT("A")>{});
	ASSERT_PARSER_VALUES_EQ(TT(""_any_of), any_of_parser<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(TT(""_none_of), none_of_parser<TT("")>{});
}
