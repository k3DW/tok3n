#include "pch.h"

FIXTURE("basic operators");

TEST("basic operators", "UDL _any")
{
	ASSERT_PARSER_VALUES_EQ("abc"_any, oc1);
	ASSERT_PARSER_VALUES_EQ("bcd"_any, oc2);
	ASSERT_PARSER_VALUES_EQ("xyz"_any, oc3);
	ASSERT_PARSER_VALUES_EQ("cd"_any, oc4);
	ASSERT_PARSER_VALUES_EQ(","_any, comma);
	ASSERT_PARSER_VALUES_EQ(" ."_any, spacedot);
	ASSERT_PARSER_VALUES_EQ(""_any, AnyOf<"">{});
}

TEST("basic operators", "any<>")
{
	ASSERT_PARSER_VALUES_EQ(any<"abc">, oc1);
	ASSERT_PARSER_VALUES_EQ(any<"bcd">, oc2);
	ASSERT_PARSER_VALUES_EQ(any<"xyz">, oc3);
	ASSERT_PARSER_VALUES_EQ(any<"cd">, oc4);
	ASSERT_PARSER_VALUES_EQ(any<",">, comma);
	ASSERT_PARSER_VALUES_EQ(any<" .">, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<"">, AnyOf<"">{});
}

TEST("basic operators", "UDL _none")
{
	ASSERT_PARSER_VALUES_EQ("abc"_none, nc1);
	ASSERT_PARSER_VALUES_EQ("bcd"_none, nc2);
	ASSERT_PARSER_VALUES_EQ("xyz"_none, nc3);
	ASSERT_PARSER_VALUES_EQ("cd"_none, nc4);
	ASSERT_PARSER_VALUES_EQ("z"_none, nc5);
	ASSERT_PARSER_VALUES_EQ(""_none, NoneOf<"">{});
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<"abc">, nc1);
	ASSERT_PARSER_VALUES_EQ(none<"bcd">, nc2);
	ASSERT_PARSER_VALUES_EQ(none<"xyz">, nc3);
	ASSERT_PARSER_VALUES_EQ(none<"cd">, nc4);
	ASSERT_PARSER_VALUES_EQ(none<"z">, nc5);
	ASSERT_PARSER_VALUES_EQ(none<"">, NoneOf<"">{});
}

TEST("basic operators", "UDL _all")
{
	ASSERT_PARSER_VALUES_EQ("literal"_all, l1);
	ASSERT_PARSER_VALUES_EQ("ly"_all, l2);
	ASSERT_PARSER_VALUES_EQ("test"_all, l3);
	ASSERT_PARSER_VALUES_EQ("ab"_all, l4);
	ASSERT_PARSER_VALUES_EQ("??"_all, qq);
	ASSERT_PARSER_VALUES_EQ("abc"_all, abc);
	ASSERT_PARSER_VALUES_EQ(""_all, AllOf<"">{});
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<"literal">, l1);
	ASSERT_PARSER_VALUES_EQ(all<"ly">, l2);
	ASSERT_PARSER_VALUES_EQ(all<"test">, l3);
	ASSERT_PARSER_VALUES_EQ(all<"ab">, l4);
	ASSERT_PARSER_VALUES_EQ(all<"??">, qq);
	ASSERT_PARSER_VALUES_EQ(all<"abc">, abc);
	ASSERT_PARSER_VALUES_EQ(all<"">, AllOf<"">{});
}

TEST("basic operators", "UDL _ign")
{
	ASSERT_PARSER_VALUES_EQ("literal"_ign, Ignore<L1>{});
	ASSERT_PARSER_VALUES_EQ("ly"_ign, Ignore<L2>{});
	ASSERT_PARSER_VALUES_EQ("test"_ign, Ignore<L3>{});
	ASSERT_PARSER_VALUES_EQ("ab"_ign, Ignore<L4>{});
	ASSERT_PARSER_VALUES_EQ("??"_ign, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ("abc"_ign, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(""_ign, Ignore<AllOf<"">>{});
}

TEST("basic operators", "ign<>")
{
	ASSERT_PARSER_VALUES_EQ(ign<"literal">, Ignore<L1>{});
	ASSERT_PARSER_VALUES_EQ(ign<"ly">, Ignore<L2>{});
	ASSERT_PARSER_VALUES_EQ(ign<"test">, Ignore<L3>{});
	ASSERT_PARSER_VALUES_EQ(ign<"ab">, Ignore<L4>{});
	ASSERT_PARSER_VALUES_EQ(ign<"??">, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<"abc">, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<"">, Ignore<AllOf<"">>{});
}

TEST("basic operators", "Non sorted_and_uniqued")
{
	ASSERT_PARSER_VALUES_EQ("212312323321212311"_any, AnyOf<"123">{});
	ASSERT_PARSER_VALUES_EQ("212312323321212311"_none, NoneOf<"123">{});
	ASSERT_PARSER_VALUES_EQ("123abc"_any, AnyOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("123abc"_none, NoneOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("abc123"_any, AnyOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("abc123"_none, NoneOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("a1b2c3"_any, AnyOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("a1b2c3"_none, NoneOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("Aa"_any, AnyOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("Aa"_none, NoneOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("aA"_any, AnyOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("aA"_none, NoneOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("A"_any, AnyOf<"A">{});
	ASSERT_PARSER_VALUES_EQ("A"_none, NoneOf<"A">{});
	ASSERT_PARSER_VALUES_EQ(""_any, AnyOf<"">{});
	ASSERT_PARSER_VALUES_EQ(""_none, NoneOf<"">{});
}
