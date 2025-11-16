// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("map modifier");

TEST("map modifier", "prefix")
{
    EXPECT_THAT(parser_value<map1>
                         .is<map<func1>(+abc)>);
    EXPECT_THAT(parser_value<map2>
                         .is<map<func2>(~(abc | qq))>);
    EXPECT_THAT(parser_value<map3>
                         .is<map<func3>(abc >> *qq)>);
    EXPECT_THAT(parser_value<map4>
                         .is<map<func4(3)>(+abc >> ~(abc | qq))>);
    EXPECT_THAT(parser_value<map4>
                     .is_not<map<func4(2)>(+abc >> ~(abc | qq))>);
}

TEST("map modifier", "infix")
{
    EXPECT_THAT(parser_value<map1>
                         .is<+abc % map<func1>>);
    EXPECT_THAT(parser_value<map2>
                         .is<~(abc | qq) % map<func2>>);
    EXPECT_THAT(parser_value<map3>
                         .is<(abc >> *qq) % map<func3>>);
    EXPECT_THAT(parser_value<map4>
                         .is<(+abc >> ~(abc | qq)) % map<func4(3)>>);
    EXPECT_THAT(parser_value<map4>
                     .is_not<(+abc >> ~(abc | qq)) % map<func4(2)>>);
}

TEST("map modifier", "non consteval")
{
    (map<sink_func>(any1)).parse(TT("abc"));
    (any1 % map<sink_func>).parse(TT("abc"));
}



#define MAP_MODIFIER_ASSERTER(P)                                                                         \
    []<parser PP>(PP) {                                                                                  \
        using R = map_parser<PP, integral_constant<sink_func>>;                                          \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<map<sink_func>>.TEMPLATE_IF_GCC12 with_result<R>); \
    }(P{});

TEST("map modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(MAP_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
