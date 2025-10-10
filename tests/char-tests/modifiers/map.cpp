// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("map modifier");

TEST("map modifier", "prefix")
{
    ASSERT_PARSER_VALUES_EQ(map1, map<func1>(+abc));
    ASSERT_PARSER_VALUES_EQ(map2, map<func2>(~(abc | qq)));
    ASSERT_PARSER_VALUES_EQ(map3, map<func3>(abc >> *qq));
    ASSERT_PARSER_VALUES_EQ(map4, map<func4(3)>(+abc >> ~(abc | qq)));
    ASSERT_PARSER_VALUES_NE(map4, map<func4(2)>(+abc >> ~(abc | qq)));
}

TEST("map modifier", "infix")
{
    ASSERT_PARSER_VALUES_EQ(map1, +abc % map<func1>);
    ASSERT_PARSER_VALUES_EQ(map2, ~(abc | qq) % map<func2>);
    ASSERT_PARSER_VALUES_EQ(map3, (abc >> *qq) % map<func3>);
    ASSERT_PARSER_VALUES_EQ(map4, (+abc >> ~(abc | qq)) % map<func4(3)>);
    ASSERT_PARSER_VALUES_NE(map4, (+abc >> ~(abc | qq)) % map<func4(2)>);
}

TEST("map modifier", "non consteval")
{
    (map<sink_func>(any1)).parse(TT("abc"));
    (any1 % map<sink_func>).parse(TT("abc"));
}



#define MAP_MODIFIER_ASSERTER(P)                                                                                      \
    []<parser PP>(PP) {                                                                                               \
        DEP_ASSERT_MODIFIER_CALLABLE_R(map<sink_func>, (PP{}), (map_parser<PP, integral_constant<sink_func>>{}),      \
                                       map<sink_func>, (P{}),  (map_parser<P, integral_constant<sink_func>>{}));      \
        DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, map<sink_func>, (map_parser<PP, integral_constant<sink_func>>{}), \
                                              P{},  map<sink_func>, (map_parser<P, integral_constant<sink_func>>{})); \
    }(P{});

TEST("map modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(MAP_MODIFIER_ASSERTER);
}
