#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("basic operators");

TEST("basic operators", "UDL _any")
{
	ASSERT_PARSER_VALUES_EQ(L"abc"_any, any1);
	ASSERT_PARSER_VALUES_EQ(L"bcd"_any, any2);
	ASSERT_PARSER_VALUES_EQ(L"xyz"_any, any3);
	ASSERT_PARSER_VALUES_EQ(L"cd"_any, any4);
	ASSERT_PARSER_VALUES_EQ(L","_any, comma);
	ASSERT_PARSER_VALUES_EQ(L" ."_any, spacedot);
	ASSERT_PARSER_VALUES_EQ(L""_any, AnyOf<L"">{});
}

TEST("basic operators", "UDL _any_of")
{
	ASSERT_PARSER_VALUES_EQ(L"abc"_any_of, any1);
	ASSERT_PARSER_VALUES_EQ(L"bcd"_any_of, any2);
	ASSERT_PARSER_VALUES_EQ(L"xyz"_any_of, any3);
	ASSERT_PARSER_VALUES_EQ(L"cd"_any_of, any4);
	ASSERT_PARSER_VALUES_EQ(L","_any_of, comma);
	ASSERT_PARSER_VALUES_EQ(L" ."_any_of, spacedot);
	ASSERT_PARSER_VALUES_EQ(L""_any_of, AnyOf<L"">{});
}

TEST("basic operators", "any<>")
{
	ASSERT_PARSER_VALUES_EQ(any<L"abc">, any1);
	ASSERT_PARSER_VALUES_EQ(any<L"bcd">, any2);
	ASSERT_PARSER_VALUES_EQ(any<L"xyz">, any3);
	ASSERT_PARSER_VALUES_EQ(any<L"cd">, any4);
	ASSERT_PARSER_VALUES_EQ(any<L",">, comma);
	ASSERT_PARSER_VALUES_EQ(any<L" .">, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<L"">, AnyOf<L"">{});
}

TEST("basic operators", "any_of<>")
{
	ASSERT_PARSER_VALUES_EQ((any_of<L'a', L'b', L'c'>), any1);
	ASSERT_PARSER_VALUES_EQ((any_of<L'b', L'c', L'd'>), any2);
	ASSERT_PARSER_VALUES_EQ((any_of<L'x', L'y', L'z'>), any3);
	ASSERT_PARSER_VALUES_EQ((any_of<L'c', L'd'>), any4);
	ASSERT_PARSER_VALUES_EQ((any_of<L','>), comma);
	ASSERT_PARSER_VALUES_EQ((any_of<L' ', L'.'>), spacedot);
}

TEST("basic operators", "UDL _none")
{
	ASSERT_PARSER_VALUES_EQ(L"abc"_none, none1);
	ASSERT_PARSER_VALUES_EQ(L"bcd"_none, none2);
	ASSERT_PARSER_VALUES_EQ(L"xyz"_none, none3);
	ASSERT_PARSER_VALUES_EQ(L"cd"_none, none4);
	ASSERT_PARSER_VALUES_EQ(L"z"_none, none5);
	ASSERT_PARSER_VALUES_EQ(L""_none, NoneOf<L"">{});
}

TEST("basic operators", "UDL _none_of")
{
	ASSERT_PARSER_VALUES_EQ(L"abc"_none_of, none1);
	ASSERT_PARSER_VALUES_EQ(L"bcd"_none_of, none2);
	ASSERT_PARSER_VALUES_EQ(L"xyz"_none_of, none3);
	ASSERT_PARSER_VALUES_EQ(L"cd"_none_of, none4);
	ASSERT_PARSER_VALUES_EQ(L"z"_none_of, none5);
	ASSERT_PARSER_VALUES_EQ(L""_none_of, NoneOf<L"">{});
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<L"abc">, none1);
	ASSERT_PARSER_VALUES_EQ(none<L"bcd">, none2);
	ASSERT_PARSER_VALUES_EQ(none<L"xyz">, none3);
	ASSERT_PARSER_VALUES_EQ(none<L"cd">, none4);
	ASSERT_PARSER_VALUES_EQ(none<L"z">, none5);
	ASSERT_PARSER_VALUES_EQ(none<L"">, NoneOf<L"">{});
}

TEST("basic operators", "none_of<>")
{
	ASSERT_PARSER_VALUES_EQ((none_of<L'a', L'b', L'c'>), none1);
	ASSERT_PARSER_VALUES_EQ((none_of<L'b', L'c', L'd'>), none2);
	ASSERT_PARSER_VALUES_EQ((none_of<L'x', L'y', L'z'>), none3);
	ASSERT_PARSER_VALUES_EQ((none_of<L'c', L'd'>), none4);
	ASSERT_PARSER_VALUES_EQ((none_of<L'z'>), none5);
}

TEST("basic operators", "UDL _all")
{
	ASSERT_PARSER_VALUES_EQ(L"literal"_all, all1);
	ASSERT_PARSER_VALUES_EQ(L"ly"_all, all2);
	ASSERT_PARSER_VALUES_EQ(L"test"_all, all3);
	ASSERT_PARSER_VALUES_EQ(L"ab"_all, all4);
	ASSERT_PARSER_VALUES_EQ(L"??"_all, qq);
	ASSERT_PARSER_VALUES_EQ(L"abc"_all, abc);
	ASSERT_PARSER_VALUES_EQ(L""_all, AllOf<L"">{});
}

TEST("basic operators", "UDL _all_of")
{
	ASSERT_PARSER_VALUES_EQ(L"literal"_all_of, all1);
	ASSERT_PARSER_VALUES_EQ(L"ly"_all_of, all2);
	ASSERT_PARSER_VALUES_EQ(L"test"_all_of, all3);
	ASSERT_PARSER_VALUES_EQ(L"ab"_all_of, all4);
	ASSERT_PARSER_VALUES_EQ(L"??"_all_of, qq);
	ASSERT_PARSER_VALUES_EQ(L"abc"_all_of, abc);
	ASSERT_PARSER_VALUES_EQ(L""_all_of, AllOf<L"">{});
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<L"literal">, all1);
	ASSERT_PARSER_VALUES_EQ(all<L"ly">, all2);
	ASSERT_PARSER_VALUES_EQ(all<L"test">, all3);
	ASSERT_PARSER_VALUES_EQ(all<L"ab">, all4);
	ASSERT_PARSER_VALUES_EQ(all<L"??">, qq);
	ASSERT_PARSER_VALUES_EQ(all<L"abc">, abc);
	ASSERT_PARSER_VALUES_EQ(all<L"">, AllOf<L"">{});
}

TEST("basic operators", "all_of<>")
{
	ASSERT_PARSER_VALUES_EQ((all_of<L'l', L'i', L't', L'e', L'r', L'a', L'l'>), all1);
	ASSERT_PARSER_VALUES_EQ((all_of<L'l', L'y'>), all2);
	ASSERT_PARSER_VALUES_EQ((all_of<L't', L'e', L's', L't'>), all3);
	ASSERT_PARSER_VALUES_EQ((all_of<L'a', L'b'>), all4);
	ASSERT_PARSER_VALUES_EQ((all_of<L'?', L'?'>), qq);
	ASSERT_PARSER_VALUES_EQ((all_of<L'a', L'b', L'c'>), abc);
}

TEST("basic operators", "UDL _ign")
{
	ASSERT_PARSER_VALUES_EQ(L"literal"_ign, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ(L"ly"_ign, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ(L"test"_ign, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ(L"ab"_ign, Ignore<All4>{});
	ASSERT_PARSER_VALUES_EQ(L"??"_ign, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(L"abc"_ign, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(L""_ign, Ignore<AllOf<L"">>{});
}

TEST("basic operators", "ign<>")
{
	ASSERT_PARSER_VALUES_EQ(ign<L"literal">, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<L"ly">, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<L"test">, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<L"ab">, Ignore<All4>{});
	ASSERT_PARSER_VALUES_EQ(ign<L"??">, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<L"abc">, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<L"">, Ignore<AllOf<L"">>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
	ASSERT_PARSER_VALUES_EQ(L"212312323321212311"_any, AnyOf<L"123">{});
	ASSERT_PARSER_VALUES_EQ(L"212312323321212311"_none, NoneOf<L"123">{});
	ASSERT_PARSER_VALUES_EQ(L"123abc"_any, AnyOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"123abc"_none, NoneOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"abc123"_any, AnyOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"abc123"_none, NoneOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"a1b2c3"_any, AnyOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"a1b2c3"_none, NoneOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"Aa"_any, AnyOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"Aa"_none, NoneOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"aA"_any, AnyOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"aA"_none, NoneOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"A"_any, AnyOf<L"A">{});
	ASSERT_PARSER_VALUES_EQ(L"A"_none, NoneOf<L"A">{});
	ASSERT_PARSER_VALUES_EQ(L""_any, AnyOf<L"">{});
	ASSERT_PARSER_VALUES_EQ(L""_none, NoneOf<L"">{});

	ASSERT_PARSER_VALUES_EQ(L"212312323321212311"_any_of, AnyOf<L"123">{});
	ASSERT_PARSER_VALUES_EQ(L"212312323321212311"_none_of, NoneOf<L"123">{});
	ASSERT_PARSER_VALUES_EQ(L"123abc"_any_of, AnyOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"123abc"_none_of, NoneOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"abc123"_any_of, AnyOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"abc123"_none_of, NoneOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"a1b2c3"_any_of, AnyOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"a1b2c3"_none_of, NoneOf<L"123abc">{});
	ASSERT_PARSER_VALUES_EQ(L"Aa"_any_of, AnyOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"Aa"_none_of, NoneOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"aA"_any_of, AnyOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"aA"_none_of, NoneOf<L"Aa">{});
	ASSERT_PARSER_VALUES_EQ(L"A"_any_of, AnyOf<L"A">{});
	ASSERT_PARSER_VALUES_EQ(L"A"_none_of, NoneOf<L"A">{});
	ASSERT_PARSER_VALUES_EQ(L""_any_of, AnyOf<L"">{});
	ASSERT_PARSER_VALUES_EQ(L""_none_of, NoneOf<L"">{});
}
