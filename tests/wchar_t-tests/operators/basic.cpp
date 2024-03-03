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
	ASSERT_PARSER_VALUES_EQ(L""_any, nothing<wchar_t>);
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
	ASSERT_PARSER_VALUES_EQ(any<L"">, nothing<wchar_t>);
}

TEST("basic operators", "UDL _none")
{
	ASSERT_PARSER_VALUES_EQ(L"abc"_none, none1);
	ASSERT_PARSER_VALUES_EQ(L"bcd"_none, none2);
	ASSERT_PARSER_VALUES_EQ(L"xyz"_none, none3);
	ASSERT_PARSER_VALUES_EQ(L"cd"_none, none4);
	ASSERT_PARSER_VALUES_EQ(L"z"_none, none5);
	ASSERT_PARSER_VALUES_EQ(L""_none, NoneOf<L"">{});
	ASSERT_PARSER_VALUES_EQ(L""_none, anything<wchar_t>);
}

TEST("basic operators", "none<>")
{
	ASSERT_PARSER_VALUES_EQ(none<L"abc">, none1);
	ASSERT_PARSER_VALUES_EQ(none<L"bcd">, none2);
	ASSERT_PARSER_VALUES_EQ(none<L"xyz">, none3);
	ASSERT_PARSER_VALUES_EQ(none<L"cd">, none4);
	ASSERT_PARSER_VALUES_EQ(none<L"z">, none5);
	ASSERT_PARSER_VALUES_EQ(none<L"">, NoneOf<L"">{});
	ASSERT_PARSER_VALUES_EQ(none<L"">, anything<wchar_t>);
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
	ASSERT_PARSER_VALUES_EQ(L""_all, eps<wchar_t>);
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
	ASSERT_PARSER_VALUES_EQ(all<L"">, eps<wchar_t>);
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
	ASSERT_PARSER_VALUES_EQ(L""_ign, Ignore<std::remove_const_t<decltype(eps<wchar_t>)>>{});
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
	ASSERT_PARSER_VALUES_EQ(ign<L"">, Ignore<std::remove_const_t<decltype(eps<wchar_t>)>>{});
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
	ASSERT_PARSER_VALUES_EQ(L""_any, nothing<wchar_t>);
	ASSERT_PARSER_VALUES_EQ(L""_none, anything<wchar_t>);
}
