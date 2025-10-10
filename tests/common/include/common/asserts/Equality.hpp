// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_ASSERTS_EQUALITY_HPP
#define K3_TOK3N_TESTS_COMMON_ASSERTS_EQUALITY_HPP

#include "framework/Assert.hpp"
#include "common/asserts/Concept.hpp"

template <auto lhs, auto rhs>
concept same_values = std::same_as<std::remove_cvref_t<decltype(lhs)>, std::remove_cvref_t<decltype(rhs)>>;



// Checking in a dependent context, so the error messages are still nice
// This wouldn't be needed if we had CWG2518 or P2593

#define DEP_ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)          \
    ASSERT((k3::tok3n::detail::parser<decltype(LHS_VALUE)>),                                 \
        "`" STR(LHS_DISPLAY) "` does not satisfy the parser concept.");                      \
    ASSERT((k3::tok3n::detail::parser<decltype(RHS_VALUE)>),                                 \
        "`" STR(RHS_DISPLAY) "` does not satisfy the parser concept.");                      \
    ASSERT((same_values<(LHS_VALUE), (RHS_VALUE)>),                                          \
        "`" STR(LHS_DISPLAY) "` and `" STR(RHS_DISPLAY) "` are not the same, but should be")

#define DEP_ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)          \
    ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(LHS_VALUE));                          \
    ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(RHS_VALUE));                          \
    ASSERT((not same_values<(LHS_VALUE), (RHS_VALUE)>),                                      \
        "`" STR(LHS_DISPLAY) "` and `" STR(RHS_DISPLAY) "` are the same, but should not be")



// Checking in a context where dependent types are not required

#define ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE) \
    DEP_ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE, LHS_VALUE, RHS_VALUE)

#define ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE) \
    DEP_ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE, LHS_VALUE, RHS_VALUE)

#define ASSERT_MODIFIER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                                  \
    ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(LHS_VALUE));                    \
    ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(RHS_VALUE));                    \
    ASSERT((same_values<(LHS_VALUE), (RHS_VALUE)>),                                      \
        "`" STR(LHS_VALUE) "` and `" STR(RHS_VALUE) "` are not the same, but should be")

#define ASSERT_MODIFIER_VALUES_NE(LHS_VALUE, RHS_VALUE)                                  \
    ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(LHS_VALUE));                    \
    ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(RHS_VALUE));                    \
    ASSERT((not same_values<(LHS_VALUE), (RHS_VALUE)>),                                  \
        "`" STR(LHS_VALUE) "` and `" STR(RHS_VALUE) "` are the same, but should not be")

#endif // K3_TOK3N_TESTS_COMMON_ASSERTS_EQUALITY_HPP
