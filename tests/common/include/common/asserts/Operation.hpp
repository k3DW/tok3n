// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_ASSERTS_OPERATION_HPP
#define K3_TOK3N_TESTS_COMMON_ASSERTS_OPERATION_HPP

#include "framework/assert.hpp"
#include "common/asserts/Concept.hpp"
#include <k3/tok3n/detail/parser.hpp>

// Checking in a dependent context, so the error messages are still nice
// This wouldn't be needed if we had CWG2518 or P2593

#define DEP_ASSERT_UNARY_OPERABLE(OPERATOR, P_VALUE, P_DISPLAY)                                                          \
    ASSERT((requires { OPERATOR (P_VALUE); })) << "`" STR(OPERATOR) STR(P_DISPLAY) "` does not compile, but it should."; \
    ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(OPERATOR P_VALUE))

#define DEP_ASSERT_UNARY_NOT_OPERABLE(OPERATOR, P_VALUE, P_DISPLAY) \
    ASSERT((not requires { OPERATOR (P_VALUE); })) << "`" STR(OPERATOR) STR(P_DISPLAY) "` compiles, but it should not."

#define DEP_ASSERT_BINARY_OPERABLE(OPERATOR, LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)                 \
    ASSERT((requires { (LHS_VALUE) OPERATOR (RHS_VALUE); }))                                                 \
        << "`" STR(LHS_DISPLAY) " " STR(OPERATOR) " " STR(RHS_DISPLAY) "` does not compile, but it should."; \
    ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(LHS_VALUE OPERATOR RHS_VALUE))

#define DEP_ASSERT_BINARY_NOT_OPERABLE(OPERATOR, LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)      \
    ASSERT((not requires { (LHS_VALUE) OPERATOR (RHS_VALUE); }))                                      \
        << "`" STR(LHS_DISPLAY) " " STR(OPERATOR) " " STR(RHS_DISPLAY) "` compiles, but it should not."

#endif // K3_TOK3N_TESTS_COMMON_ASSERTS_OPERATION_HPP
