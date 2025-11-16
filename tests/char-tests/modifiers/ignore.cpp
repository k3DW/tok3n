// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("ignore modifier");

TEST("ignore modifier", "prefix")
{
    EXPECT_THAT(parser_value<ign1>
                         .is<ignore(abc)>);
    EXPECT_THAT(parser_value<ign2>
                         .is<ignore(+abc)>);
    EXPECT_THAT(parser_value<ign3>
                         .is<ignore(~(abc | qq))>);
    EXPECT_THAT(parser_value<ign4>
                         .is<ignore(abc >> *qq)>);
    EXPECT_THAT(parser_value<ign5>
                         .is<ignore(+abc >> ~(abc | qq))>);
}

TEST("ignore modifier", "infix")
{
    EXPECT_THAT(parser_value<ign1>
                         .is<abc % ignore>);
    EXPECT_THAT(parser_value<ign2>
                         .is<+abc % ignore>);
    EXPECT_THAT(parser_value<ign3>
                         .is<~(abc | qq) % ignore>);
    EXPECT_THAT(parser_value<ign4>
                         .is<(abc >> *qq) % ignore>);
    EXPECT_THAT(parser_value<ign5>
                         .is<(+abc >> ~(abc | qq)) % ignore>);
}

TEST("ignore modifier", "idempotent")
{
    EXPECT_THAT(parser_value<ign1>
                         .is<ignore(ign1)>);
    EXPECT_THAT(parser_value<ign2>
                         .is<ignore(ign2)>);
    EXPECT_THAT(parser_value<ign3>
                         .is<ignore(ign3)>);
    EXPECT_THAT(parser_value<ign4>
                         .is<ignore(ign4)>);
    EXPECT_THAT(parser_value<ign5>
                         .is<ignore(ign5)>);
    EXPECT_THAT(parser_value<ign1>
                         .is<ign1 % ignore>);
    EXPECT_THAT(parser_value<ign2>
                         .is<ign2 % ignore>);
    EXPECT_THAT(parser_value<ign3>
                         .is<ign3 % ignore>);
    EXPECT_THAT(parser_value<ign4>
                         .is<ign4 % ignore>);
    EXPECT_THAT(parser_value<ign5>
                         .is<ign5 % ignore>);
}

TEST("ignore modifier", "non consteval")
{
    (ignore(any1)).parse(TT("abc"));
    (any1 % ignore).parse(TT("abc"));
}



constexpr auto ignore_modifier_fragment =
    []<detail::parser P>(P) {
        if constexpr (P::family == ignore_family)
        {
            EXPECT_THAT(the_parser<P> | is_modifiable_by<ignore>.TEMPLATE_IF_GCC12 with_result<P>);
        }
        else
        {
            EXPECT_THAT(the_parser<P> | is_modifiable_by<ignore>.TEMPLATE_IF_GCC12 with_result<ignore_parser<P>>);
        }
    };

TEST("ignore modifier", "modify anything")
{
    EXPECT_THAT(all_samples.satisfy(ignore_modifier_fragment));
}

} // namespace
} // namespace k3::tok3n::tests
