// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply_into modifier");

TEST("apply_into modifier", "prefix")
{
    EXPECT_THAT(parser_value<api1>
                         .is<apply_into<Class2>(abc >> spacedot)>);
    EXPECT_THAT(parser_value<api2>
                         .is<apply_into<Class5>(spacedot >> abc)>);
}

TEST("apply_into modifier", "infix")
{
    EXPECT_THAT(parser_value<api1>
                         .is<(abc >> spacedot) % apply_into<Class2>>);
    EXPECT_THAT(parser_value<api2>
                         .is<(spacedot >> abc) % apply_into<Class5>>);
}

TEST("apply_into modifier", "non consteval")
{
    (apply_into<Sink>(any1 >> any2)).parse(TT("abc"));
    ((any1 >> any2) % apply_into<Sink>).parse(TT("abc"));
}



constexpr auto apply_into_modifier_fragment =
    []<detail::parser P>(P) {
        constexpr auto m = apply_into<Sink>;
        using R = apply_into_parser<P, Sink>;
        EXPECT_THAT(the_parser<P> | is_modifiable_by<m>.TEMPLATE_IF_GCC12 with_result<R>);
    };

TEST("apply_into modifier", "modify anything")
{
    EXPECT_THAT(all_samples.satisfy(apply_into_modifier_fragment));
}

} // namespace
} // namespace k3::tok3n::tests
