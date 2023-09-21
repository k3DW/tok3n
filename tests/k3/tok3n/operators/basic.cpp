#include "pch.h"

FIXTURE("basic operators");

TEST("basic operators", "UDL _one")
{
	ASSERT_PARSER_VALUES_EQ("abc"_one, oc1);
	ASSERT_PARSER_VALUES_EQ("bcd"_one, oc2);
	ASSERT_PARSER_VALUES_EQ("xyz"_one, oc3);
	ASSERT_PARSER_VALUES_EQ("cd"_one, oc4);
	ASSERT_PARSER_VALUES_EQ(","_one, comma);
	ASSERT_PARSER_VALUES_EQ(" ."_one, spacedot);
	ASSERT_PARSER_VALUES_EQ(""_one, AnyOf<"">{});
}

TEST("basic operators", "one<>")
{
	ASSERT_PARSER_VALUES_EQ(one<"abc">, oc1);
	ASSERT_PARSER_VALUES_EQ(one<"bcd">, oc2);
	ASSERT_PARSER_VALUES_EQ(one<"xyz">, oc3);
	ASSERT_PARSER_VALUES_EQ(one<"cd">, oc4);
	ASSERT_PARSER_VALUES_EQ(one<",">, comma);
	ASSERT_PARSER_VALUES_EQ(one<" .">, spacedot);
	ASSERT_PARSER_VALUES_EQ(one<"">, AnyOf<"">{});
}

TEST("basic operators", "UDL _not")
{
	ASSERT_PARSER_VALUES_EQ("abc"_not, nc1);
	ASSERT_PARSER_VALUES_EQ("bcd"_not, nc2);
	ASSERT_PARSER_VALUES_EQ("xyz"_not, nc3);
	ASSERT_PARSER_VALUES_EQ("cd"_not, nc4);
	ASSERT_PARSER_VALUES_EQ("z"_not, nc5);
	ASSERT_PARSER_VALUES_EQ(""_not, NoneOf<"">{});
}

TEST("basic operators", "not_<>")
{
	ASSERT_PARSER_VALUES_EQ(not_<"abc">, nc1);
	ASSERT_PARSER_VALUES_EQ(not_<"bcd">, nc2);
	ASSERT_PARSER_VALUES_EQ(not_<"xyz">, nc3);
	ASSERT_PARSER_VALUES_EQ(not_<"cd">, nc4);
	ASSERT_PARSER_VALUES_EQ(not_<"z">, nc5);
	ASSERT_PARSER_VALUES_EQ(not_<"">, NoneOf<"">{});
}

TEST("basic operators", "UDL _lit")
{
	ASSERT_PARSER_VALUES_EQ("literal"_lit, l1);
	ASSERT_PARSER_VALUES_EQ("ly"_lit, l2);
	ASSERT_PARSER_VALUES_EQ("test"_lit, l3);
	ASSERT_PARSER_VALUES_EQ("ab"_lit, l4);
	ASSERT_PARSER_VALUES_EQ("??"_lit, qq);
	ASSERT_PARSER_VALUES_EQ("abc"_lit, abc);
	ASSERT_PARSER_VALUES_EQ(""_lit, AllOf<"">{});
}

TEST("basic operators", "lit<>")
{
	ASSERT_PARSER_VALUES_EQ(lit<"literal">, l1);
	ASSERT_PARSER_VALUES_EQ(lit<"ly">, l2);
	ASSERT_PARSER_VALUES_EQ(lit<"test">, l3);
	ASSERT_PARSER_VALUES_EQ(lit<"ab">, l4);
	ASSERT_PARSER_VALUES_EQ(lit<"??">, qq);
	ASSERT_PARSER_VALUES_EQ(lit<"abc">, abc);
	ASSERT_PARSER_VALUES_EQ(lit<"">, AllOf<"">{});
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
	ASSERT_PARSER_VALUES_EQ("212312323321212311"_one, AnyOf<"123">{});
	ASSERT_PARSER_VALUES_EQ("212312323321212311"_not, NoneOf<"123">{});
	ASSERT_PARSER_VALUES_EQ("123abc"_one, AnyOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("123abc"_not, NoneOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("abc123"_one, AnyOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("abc123"_not, NoneOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("a1b2c3"_one, AnyOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("a1b2c3"_not, NoneOf<"123abc">{});
	ASSERT_PARSER_VALUES_EQ("Aa"_one, AnyOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("Aa"_not, NoneOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("aA"_one, AnyOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("aA"_not, NoneOf<"Aa">{});
	ASSERT_PARSER_VALUES_EQ("A"_one, AnyOf<"A">{});
	ASSERT_PARSER_VALUES_EQ("A"_not, NoneOf<"A">{});
	ASSERT_PARSER_VALUES_EQ(""_one, AnyOf<"">{});
	ASSERT_PARSER_VALUES_EQ(""_not, NoneOf<"">{});
}
