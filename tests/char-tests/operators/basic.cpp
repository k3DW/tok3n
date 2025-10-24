// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("basic operators");

TEST("basic operators", "UDL _any")
{
    EXPECT_THAT(parser_value<TT("abc"_any)>
                         .is<any1>);
    EXPECT_THAT(parser_value<TT("bcd"_any)>
                         .is<any2>);
    EXPECT_THAT(parser_value<TT("xyz"_any)>
                         .is<any3>);
    EXPECT_THAT(parser_value<TT("cd"_any)>
                         .is<any4>);
    EXPECT_THAT(parser_value<TT(","_any)>
                         .is<comma>);
    EXPECT_THAT(parser_value<TT(" ."_any)>
                         .is<spacedot>);
    EXPECT_THAT(parser_value<TT(""_any)>
                         .is<any_of_parser<TT("")>{}>);
}

TEST("basic operators", "UDL _any_of")
{
    EXPECT_THAT(parser_value<TT("abc"_any_of)>
                         .is<any1>);
    EXPECT_THAT(parser_value<TT("bcd"_any_of)>
                         .is<any2>);
    EXPECT_THAT(parser_value<TT("xyz"_any_of)>
                         .is<any3>);
    EXPECT_THAT(parser_value<TT("cd"_any_of)>
                         .is<any4>);
    EXPECT_THAT(parser_value<TT(","_any_of)>
                         .is<comma>);
    EXPECT_THAT(parser_value<TT(" ."_any_of)>
                         .is<spacedot>);
    EXPECT_THAT(parser_value<TT(""_any_of)>
                         .is<any_of_parser<TT("")>{}>);
}

TEST("basic operators", "any<>")
{
    EXPECT_THAT(parser_value<any<TT("abc")>>
                         .is<any1>);
    EXPECT_THAT(parser_value<any<TT("bcd")>>
                         .is<any2>);
    EXPECT_THAT(parser_value<any<TT("xyz")>>
                         .is<any3>);
    EXPECT_THAT(parser_value<any<TT("cd")>>
                         .is<any4>);
    EXPECT_THAT(parser_value<any<TT(",")>>
                         .is<comma>);
    EXPECT_THAT(parser_value<any<TT(" .")>>
                         .is<spacedot>);
    EXPECT_THAT(parser_value<any<TT("")>>
                         .is<any_of_parser<TT("")>{}>);
}

TEST("basic operators", "any_of<>")
{
    EXPECT_THAT(parser_value<(any_of<TT('a'), TT('b'), TT('c')>)>
                         .is<any1>);
    EXPECT_THAT(parser_value<(any_of<TT('b'), TT('c'), TT('d')>)>
                         .is<any2>);
    EXPECT_THAT(parser_value<(any_of<TT('x'), TT('y'), TT('z')>)>
                         .is<any3>);
    EXPECT_THAT(parser_value<(any_of<TT('c'), TT('d')>)>
                         .is<any4>);
    EXPECT_THAT(parser_value<any_of<TT(',')>>
                         .is<comma>);
    EXPECT_THAT(parser_value<(any_of<TT(' '), TT('.')>)>
                         .is<spacedot>);
}

TEST("basic operators", "UDL _none")
{
    EXPECT_THAT(parser_value<TT("abc"_none)>
                         .is<none1>);
    EXPECT_THAT(parser_value<TT("bcd"_none)>
                         .is<none2>);
    EXPECT_THAT(parser_value<TT("xyz"_none)>
                         .is<none3>);
    EXPECT_THAT(parser_value<TT("cd"_none)>
                         .is<none4>);
    EXPECT_THAT(parser_value<TT("z"_none)>
                         .is<none5>);
    EXPECT_THAT(parser_value<TT(""_none)>
                         .is<none_of_parser<TT("")>{}>);
}

TEST("basic operators", "UDL _none_of")
{
    EXPECT_THAT(parser_value<TT("abc"_none_of)>
                         .is<none1>);
    EXPECT_THAT(parser_value<TT("bcd"_none_of)>
                         .is<none2>);
    EXPECT_THAT(parser_value<TT("xyz"_none_of)>
                         .is<none3>);
    EXPECT_THAT(parser_value<TT("cd"_none_of)>
                         .is<none4>);
    EXPECT_THAT(parser_value<TT("z"_none_of)>
                         .is<none5>);
    EXPECT_THAT(parser_value<TT(""_none_of)>
                         .is<none_of_parser<TT("")>{}>);
}

TEST("basic operators", "none<>")
{
    EXPECT_THAT(parser_value<none<TT("abc")>>
                         .is<none1>);
    EXPECT_THAT(parser_value<none<TT("bcd")>>
                         .is<none2>);
    EXPECT_THAT(parser_value<none<TT("xyz")>>
                         .is<none3>);
    EXPECT_THAT(parser_value<none<TT("cd")>>
                         .is<none4>);
    EXPECT_THAT(parser_value<none<TT("z")>>
                         .is<none5>);
    EXPECT_THAT(parser_value<none<TT("")>>
                         .is<none_of_parser<TT("")>{}>);
}

TEST("basic operators", "none_of<>")
{
    EXPECT_THAT(parser_value<(none_of<TT('a'), TT('b'), TT('c')>)>
                         .is<none1>);
    EXPECT_THAT(parser_value<(none_of<TT('b'), TT('c'), TT('d')>)>
                         .is<none2>);
    EXPECT_THAT(parser_value<(none_of<TT('x'), TT('y'), TT('z')>)>
                         .is<none3>);
    EXPECT_THAT(parser_value<(none_of<TT('c'), TT('d')>)>
                         .is<none4>);
    EXPECT_THAT(parser_value<(none_of<TT('z')>)>
                         .is<none5>);
}

TEST("basic operators", "UDL _all")
{
    EXPECT_THAT(parser_value<TT("literal"_all)>
                         .is<all1>);
    EXPECT_THAT(parser_value<TT("ly"_all)>
                         .is<all2>);
    EXPECT_THAT(parser_value<TT("test"_all)>
                         .is<all3>);
    EXPECT_THAT(parser_value<TT("ab"_all)>
                         .is<all4>);
    EXPECT_THAT(parser_value<TT("??"_all)>
                         .is<qq>);
    EXPECT_THAT(parser_value<TT("abc"_all)>
                         .is<abc>);
    EXPECT_THAT(parser_value<TT(""_all)>
                         .is<all_of_parser<TT("")>{}>);
}

TEST("basic operators", "UDL _all_of")
{
    EXPECT_THAT(parser_value<TT("literal"_all_of)>
                         .is<all1>);
    EXPECT_THAT(parser_value<TT("ly"_all_of)>
                         .is<all2>);
    EXPECT_THAT(parser_value<TT("test"_all_of)>
                         .is<all3>);
    EXPECT_THAT(parser_value<TT("ab"_all_of)>
                         .is<all4>);
    EXPECT_THAT(parser_value<TT("??"_all_of)>
                         .is<qq>);
    EXPECT_THAT(parser_value<TT("abc"_all_of)>
                         .is<abc>);
    EXPECT_THAT(parser_value<TT(""_all_of)>
                         .is<all_of_parser<TT("")>{}>);
}

TEST("basic operators", "all<>")
{
    EXPECT_THAT(parser_value<all<TT("literal")>>
                         .is<all1>);
    EXPECT_THAT(parser_value<all<TT("ly")>>
                         .is<all2>);
    EXPECT_THAT(parser_value<all<TT("test")>>
                         .is<all3>);
    EXPECT_THAT(parser_value<all<TT("ab")>>
                         .is<all4>);
    EXPECT_THAT(parser_value<all<TT("??")>>
                         .is<qq>);
    EXPECT_THAT(parser_value<all<TT("abc")>>
                         .is<abc>);
    EXPECT_THAT(parser_value<all<TT("")>>
                         .is<all_of_parser<TT("")>{}>);
}

TEST("basic operators", "all_of<>")
{
    EXPECT_THAT(parser_value<(all_of<TT('l'), TT('i'), TT('t'), TT('e'), TT('r'), TT('a'), TT('l')>)>
                         .is<all1>);
    EXPECT_THAT(parser_value<(all_of<TT('l'), TT('y')>)>
                         .is<all2>);
    EXPECT_THAT(parser_value<(all_of<TT('t'), TT('e'), TT('s'), TT('t')>)>
                         .is<all3>);
    EXPECT_THAT(parser_value<(all_of<TT('a'), TT('b')>)>
                         .is<all4>);
    EXPECT_THAT(parser_value<(all_of<TT('?'), TT('?')>)>
                         .is<qq>);
    EXPECT_THAT(parser_value<(all_of<TT('a'), TT('b'), TT('c')>)>
                         .is<abc>);
}

TEST("basic operators", "UDL _ign")
{
    EXPECT_THAT(parser_value<TT("literal"_ign)>
                         .is<ignore_parser<All1>{}>);
    EXPECT_THAT(parser_value<TT("ly"_ign)>
                         .is<ignore_parser<All2>{}>);
    EXPECT_THAT(parser_value<TT("test"_ign)>
                         .is<ignore_parser<All3>{}>);
    EXPECT_THAT(parser_value<TT("ab"_ign)>
                         .is<ignore_parser<All4>{}>);
    EXPECT_THAT(parser_value<TT("??"_ign)>
                         .is<ignore_parser<QQ>{}>);
    EXPECT_THAT(parser_value<TT("abc"_ign)>
                         .is<ignore_parser<ABC>{}>);
    EXPECT_THAT(parser_value<TT(""_ign)>
                         .is<ignore_parser<all_of_parser<TT("")>>{}>);
}

TEST("basic operators", "ign<>")
{
    EXPECT_THAT(parser_value<ign<TT("literal")>>
                         .is<ignore_parser<All1>{}>);
    EXPECT_THAT(parser_value<ign<TT("ly")>>
                         .is<ignore_parser<All2>{}>);
    EXPECT_THAT(parser_value<ign<TT("test")>>
                         .is<ignore_parser<All3>{}>);
    EXPECT_THAT(parser_value<ign<TT("ab")>>
                         .is<ignore_parser<All4>{}>);
    EXPECT_THAT(parser_value<ign<TT("??")>>
                         .is<ignore_parser<QQ>{}>);
    EXPECT_THAT(parser_value<ign<TT("abc")>>
                         .is<ignore_parser<ABC>{}>);
    EXPECT_THAT(parser_value<ign<TT("")>>
                         .is<ignore_parser<all_of_parser<TT("")>>{}>);
}

TEST("basic operators", "Non sorted_and_uniqued")
{
    EXPECT_THAT(parser_value<TT("212312323321212311"_any)>
                         .is<any_of_parser<TT("123")>{}>);
    EXPECT_THAT(parser_value<TT("212312323321212311"_none)>
                         .is<none_of_parser<TT("123")>{}>);
    EXPECT_THAT(parser_value<TT("123abc"_any)>
                         .is<any_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("123abc"_none)>
                         .is<none_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("abc123"_any)>
                         .is<any_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("abc123"_none)>
                         .is<none_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("a1b2c3"_any)>
                         .is<any_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("a1b2c3"_none)>
                         .is<none_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("Aa"_any)>
                         .is<any_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("Aa"_none)>
                         .is<none_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("aA"_any)>
                         .is<any_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("aA"_none)>
                         .is<none_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("A"_any)>
                         .is<any_of_parser<TT("A")>{}>);
    EXPECT_THAT(parser_value<TT("A"_none)>
                         .is<none_of_parser<TT("A")>{}>);
    EXPECT_THAT(parser_value<TT(""_any)>
                         .is<any_of_parser<TT("")>{}>);
    EXPECT_THAT(parser_value<TT(""_none)>
                         .is<none_of_parser<TT("")>{}>);

    EXPECT_THAT(parser_value<TT("212312323321212311"_any_of)>
                         .is<any_of_parser<TT("123")>{}>);
    EXPECT_THAT(parser_value<TT("212312323321212311"_none_of)>
                         .is<none_of_parser<TT("123")>{}>);
    EXPECT_THAT(parser_value<TT("123abc"_any_of)>
                         .is<any_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("123abc"_none_of)>
                         .is<none_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("abc123"_any_of)>
                         .is<any_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("abc123"_none_of)>
                         .is<none_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("a1b2c3"_any_of)>
                         .is<any_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("a1b2c3"_none_of)>
                         .is<none_of_parser<TT("123abc")>{}>);
    EXPECT_THAT(parser_value<TT("Aa"_any_of)>
                         .is<any_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("Aa"_none_of)>
                         .is<none_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("aA"_any_of)>
                         .is<any_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("aA"_none_of)>
                         .is<none_of_parser<TT("Aa")>{}>);
    EXPECT_THAT(parser_value<TT("A"_any_of)>
                         .is<any_of_parser<TT("A")>{}>);
    EXPECT_THAT(parser_value<TT("A"_none_of)>
                         .is<none_of_parser<TT("A")>{}>);
    EXPECT_THAT(parser_value<TT(""_any_of)>
                         .is<any_of_parser<TT("")>{}>);
    EXPECT_THAT(parser_value<TT(""_none_of)>
                         .is<none_of_parser<TT("")>{}>);
}

} // namespace
} // namespace k3::tok3n::tests
