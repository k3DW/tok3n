// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("into modifier");

TEST("into modifier", "prefix")
{
    EXPECT_THAT(parser_value<int1>
                         .is<into<Class1>(spacedot)>);
    EXPECT_THAT(parser_value<int2>
                         .is<into<Class2>(abc >> spacedot)>);
}

TEST("into modifier", "infix")
{
    EXPECT_THAT(parser_value<int1>
                         .is<spacedot % into<Class1>>);
    EXPECT_THAT(parser_value<int2>
                         .is<(abc >> spacedot) % into<Class2>>);
}

TEST("into modifier", "non consteval")
{
    (into<Sink>(any1)).parse(TT("abc"));
    (any1 % into<Sink>).parse(TT("abc"));
}



constexpr auto into_modifier_fragment =
    []<detail::parser P>(P) {
        using R = into_parser<P, Sink>;
        EXPECT_THAT(the_parser<P> | is_modifiable_by<into<Sink>>.TEMPLATE_IF_GCC12 with_result<R>);
    };

TEST("into modifier", "modify anything")
{
    EXPECT_THAT(all_samples.satisfy(into_modifier_fragment));
}

} // namespace
} // namespace k3::tok3n::tests
