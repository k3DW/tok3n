// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("complete modifier");

TEST("complete modifier", "prefix")
{
    EXPECT_THAT(parser_value<com1>
                         .is<complete(all1)>);
    EXPECT_THAT(parser_value<com2>
                         .is<complete(any1)>);
    EXPECT_THAT(parser_value<com3>
                         .is<complete(all1 | any1)>);
    EXPECT_THAT(parser_value<com4>
                         .is<complete(all1 >> any1)>);
    EXPECT_THAT(parser_value<com5>
                         .is<complete(~(all1 >> any1))>);
    EXPECT_THAT(parser_value<com6>
                         .is<complete(+(all1 >> any1))>);
    EXPECT_THAT(parser_value<com7>
                         .is<complete(*(all1 >> any1))>);
}

TEST("complete modifier", "infix")
{
    EXPECT_THAT(parser_value<com1>
                         .is<all1 % complete>);
    EXPECT_THAT(parser_value<com2>
                         .is<any1 % complete>);
    EXPECT_THAT(parser_value<com3>
                         .is<(all1 | any1) % complete>);
    EXPECT_THAT(parser_value<com4>
                         .is<(all1 >> any1) % complete>);
    EXPECT_THAT(parser_value<com5>
                         .is<~(all1 >> any1) % complete>);
    EXPECT_THAT(parser_value<com6>
                         .is<+(all1 >> any1) % complete>);
    EXPECT_THAT(parser_value<com7>
                         .is<*(all1 >> any1) % complete>);
}

TEST("complete modifier", "idempotent")
{
    EXPECT_THAT(parser_value<com1>
                         .is<complete(com1)>);
    EXPECT_THAT(parser_value<com2>
                         .is<complete(com2)>);
    EXPECT_THAT(parser_value<com3>
                         .is<complete(com3)>);
    EXPECT_THAT(parser_value<com4>
                         .is<complete(com4)>);
    EXPECT_THAT(parser_value<com5>
                         .is<complete(com5)>);
    EXPECT_THAT(parser_value<com6>
                         .is<complete(com6)>);
    EXPECT_THAT(parser_value<com7>
                         .is<complete(com7)>);
    EXPECT_THAT(parser_value<com1>
                         .is<com1 % complete>);
    EXPECT_THAT(parser_value<com2>
                         .is<com2 % complete>);
    EXPECT_THAT(parser_value<com3>
                         .is<com3 % complete>);
    EXPECT_THAT(parser_value<com4>
                         .is<com4 % complete>);
    EXPECT_THAT(parser_value<com5>
                         .is<com5 % complete>);
    EXPECT_THAT(parser_value<com6>
                         .is<com6 % complete>);
    EXPECT_THAT(parser_value<com7>
                         .is<com7 % complete>);
}

TEST("complete modifier", "non consteval")
{
    (complete(any1)).parse(TT("abc"));
    (any1 % complete).parse(TT("abc"));
}



#define COMPLETE_MODIFIER_ASSERTER(P)                                            \
    []<parser PP>(PP) {                                                          \
        using R = std::conditional_t<PP::family == complete_family,              \
            PP, complete_parser<PP>>;                                            \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<complete>.with_result<R>); \
    }(P{});

TEST("complete modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(COMPLETE_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
