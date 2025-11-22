// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("multi operator");

TEST("multi operator", "creation")
{
    EXPECT_THAT(modifier_value<ignore % join>
                           .is<(multi_modifier<ignore_modifier, join_modifier>{})>);
    EXPECT_THAT(modifier_value<join % ignore>
                           .is<(multi_modifier<join_modifier, ignore_modifier>{})>);
    EXPECT_THAT(modifier_value<complete % join>
                           .is<(multi_modifier<complete_modifier, join_modifier>{})>);
    EXPECT_THAT(modifier_value<join % complete>
                           .is<(multi_modifier<join_modifier, complete_modifier>{})>);
    EXPECT_THAT(modifier_value<ignore % complete>
                           .is<(multi_modifier<ignore_modifier, complete_modifier>{})>);
    EXPECT_THAT(modifier_value<complete % ignore>
                           .is<(multi_modifier<complete_modifier, ignore_modifier>{})>);
}

TEST("multi operator", "not commutative")
{
    EXPECT_THAT(modifier_value<(ignore % join)>
                       .is_not<(join % ignore)>);
    EXPECT_THAT(modifier_value<(complete % join)>
                       .is_not<(join % complete)>);
    EXPECT_THAT(modifier_value<(ignore % complete)>
                       .is_not<(complete % ignore)>);
}

TEST("multi operator", "associative")
{
    EXPECT_THAT(modifier_value<((ignore % join) % complete) % into<Sink>>
                           .is<(ignore % (join % complete)) % into<Sink>>);
    EXPECT_THAT(modifier_value<((ignore % join) % complete) % into<Sink>>
                           .is<(ignore % join) % (complete % into<Sink>)>);
    EXPECT_THAT(modifier_value<((ignore % join) % complete) % into<Sink>>
                           .is<ignore % ((join % complete) % into<Sink>)>);
    EXPECT_THAT(modifier_value<((ignore % join) % complete) % into<Sink>>
                           .is<ignore % (join % (complete % into<Sink>))>);
}

TEST("multi operator", "applying the modifier")
{
    EXPECT_THAT(parser_value<oom1 % (join % ignore % complete)>
                         .is<complete_parser<ignore_parser<join_parser<Oom1>>>{}>);
    EXPECT_THAT(parser_value<oom1 % (join % complete % ignore)>
                         .is<ignore_parser<complete_parser<join_parser<Oom1>>>{}>);
}

} // namespace
} // namespace k3::tok3n::tests
