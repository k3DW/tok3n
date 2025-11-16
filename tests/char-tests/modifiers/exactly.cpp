// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("exactly modifier");

TEST("exactly modifier", "prefix")
{
    EXPECT_THAT(parser_value<exa1>
                         .is<exactly<3>(all1)>);
    EXPECT_THAT(parser_value<exa2>
                         .is<exactly<5>(any1)>);
    EXPECT_THAT(parser_value<exa3>
                         .is<exactly<4>(all1 | any1)>);
    EXPECT_THAT(parser_value<exa4>
                         .is<exactly<2>(all1 >> any1)>);
}

TEST("exactly modifier", "infix")
{
    EXPECT_THAT(parser_value<exa1>
                         .is<all1 % exactly<3>>);
    EXPECT_THAT(parser_value<exa2>
                         .is<any1 % exactly<5>>);
    EXPECT_THAT(parser_value<exa3>
                         .is<(all1 | any1) % exactly<4>>);
    EXPECT_THAT(parser_value<exa4>
                         .is<(all1 >> any1) % exactly<2>>);
}

TEST("exactly modifier", "non consteval")
{
    (exactly<2>(any1)).parse(TT("abc"));
    (any1 % exactly<2>).parse(TT("abc"));
}



#define EXACTLY_MODIFIER_ASSERTER(P)                                                                 \
    []<parser PP>(PP) {                                                                              \
        using R = exactly_parser<PP, index_c<2>>;                                                    \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<exactly<2>>.TEMPLATE_IF_GCC12 with_result<R>); \
    }(P{});

TEST("exactly modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(EXACTLY_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
