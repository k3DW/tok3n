#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("basic operators");

TEST("basic operators", "UDL _any")
{
	ASSERT_PARSER_VALUES_EQ("abc"_any, any1);
	ASSERT_PARSER_VALUES_EQ("bcd"_any, any2);
	ASSERT_PARSER_VALUES_EQ("xyz"_any, any3);
	ASSERT_PARSER_VALUES_EQ("cd"_any, any4);
	ASSERT_PARSER_VALUES_EQ(","_any, comma);
	ASSERT_PARSER_VALUES_EQ(" ."_any, spacedot);
	ASSERT_PARSER_VALUES_EQ(""_any, AnyOf<"">{});
	ASSERT_PARSER_VALUES_EQ(""_any, nothing<char>);
}

TEST("basic operators", "any<>")
{
	ASSERT_PARSER_VALUES_EQ(any<"abc">, any1);
	ASSERT_PARSER_VALUES_EQ(any<"bcd">, any2);
	ASSERT_PARSER_VALUES_EQ(any<"xyz">, any3);
	ASSERT_PARSER_VALUES_EQ(any<"cd">, any4);
	ASSERT_PARSER_VALUES_EQ(any<",">, comma);
	ASSERT_PARSER_VALUES_EQ(any<" .">, spacedot);
	ASSERT_PARSER_VALUES_EQ(any<"">, AnyOf<"">{});
	ASSERT_PARSER_VALUES_EQ(any<"">, nothing<char>);
}

TEST("basic operators", "UDL _none")
{
	ASSERT_PARSER_VALUES_EQ("abc"_none, none1);
	ASSERT_PARSER_VALUES_EQ("bcd"_none, none2);
	ASSERT_PARSER_VALUES_EQ("xyz"_none, none3);
	ASSERT_PARSER_VALUES_EQ("cd"_none, none4);
	ASSERT_PARSER_VALUES_EQ("z"_none, none5);
	ASSERT_PARSER_VALUES_EQ(""_none, NoneOf<"">{});
	ASSERT_PARSER_VALUES_EQ(""_none, anything<char>);
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<"abc">, none1);
	ASSERT_PARSER_VALUES_EQ(none<"bcd">, none2);
	ASSERT_PARSER_VALUES_EQ(none<"xyz">, none3);
	ASSERT_PARSER_VALUES_EQ(none<"cd">, none4);
	ASSERT_PARSER_VALUES_EQ(none<"z">, none5);
	ASSERT_PARSER_VALUES_EQ(none<"">, NoneOf<"">{});
	ASSERT_PARSER_VALUES_EQ(none<"">, anything<char>);
}

TEST("basic operators", "UDL _all")
{
	ASSERT_PARSER_VALUES_EQ("literal"_all, all1);
	ASSERT_PARSER_VALUES_EQ("ly"_all, all2);
	ASSERT_PARSER_VALUES_EQ("test"_all, all3);
	ASSERT_PARSER_VALUES_EQ("ab"_all, all4);
	ASSERT_PARSER_VALUES_EQ("??"_all, qq);
	ASSERT_PARSER_VALUES_EQ("abc"_all, abc);
	ASSERT_PARSER_VALUES_EQ(""_all, AllOf<"">{});
	ASSERT_PARSER_VALUES_EQ(""_all, eps<char>);
}

TEST("basic operators", "all<>")
{
	ASSERT_PARSER_VALUES_EQ(all<"literal">, all1);
	ASSERT_PARSER_VALUES_EQ(all<"ly">, all2);
	ASSERT_PARSER_VALUES_EQ(all<"test">, all3);
	ASSERT_PARSER_VALUES_EQ(all<"ab">, all4);
	ASSERT_PARSER_VALUES_EQ(all<"??">, qq);
	ASSERT_PARSER_VALUES_EQ(all<"abc">, abc);
	ASSERT_PARSER_VALUES_EQ(all<"">, AllOf<"">{});
	ASSERT_PARSER_VALUES_EQ(all<"">, eps<char>);
}

TEST("basic operators", "UDL _ign")
{
	ASSERT_PARSER_VALUES_EQ("literal"_ign, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ("ly"_ign, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ("test"_ign, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ("ab"_ign, Ignore<All4>{});
	ASSERT_PARSER_VALUES_EQ("??"_ign, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ("abc"_ign, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(""_ign, Ignore<AllOf<"">>{});
	ASSERT_PARSER_VALUES_EQ(""_ign, Ignore<std::remove_const_t<decltype(eps<char>)>>{});
}

TEST("basic operators", "ign<>")
{
	ASSERT_PARSER_VALUES_EQ(ign<"literal">, Ignore<All1>{});
	ASSERT_PARSER_VALUES_EQ(ign<"ly">, Ignore<All2>{});
	ASSERT_PARSER_VALUES_EQ(ign<"test">, Ignore<All3>{});
	ASSERT_PARSER_VALUES_EQ(ign<"ab">, Ignore<All4>{});
	ASSERT_PARSER_VALUES_EQ(ign<"??">, Ignore<QQ>{});
	ASSERT_PARSER_VALUES_EQ(ign<"abc">, Ignore<ABC>{});
	ASSERT_PARSER_VALUES_EQ(ign<"">, Ignore<AllOf<"">>{});
	ASSERT_PARSER_VALUES_EQ(ign<"">, Ignore<std::remove_const_t<decltype(eps<char>)>>{});
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
	ASSERT_PARSER_VALUES_EQ(""_any, nothing<char>);
	ASSERT_PARSER_VALUES_EQ(""_none, anything<char>);
}
