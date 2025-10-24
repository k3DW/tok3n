// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_ASSERTS_CONCEPT_HPP
#define K3_TOK3N_TESTS_COMMON_ASSERTS_CONCEPT_HPP

#include "framework/assert.hpp"
#include <k3/tok3n/detail/parser.hpp>

#define IDENTITY(...) __VA_ARGS__

#define STR(...) #__VA_ARGS__

#define ASSERT_CONCEPT(Concept, ...)                                               \
    ASSERT((Concept<__VA_ARGS__>))                                                 \
        << "`" STR(__VA_ARGS__) "` does not satisfy the " STR(Concept) " concept."

#define ASSERT_NOT_CONCEPT(Concept, ...)                                                    \
    ASSERT(not (Concept<__VA_ARGS__>))                                                      \
        << "`" STR(__VA_ARGS__) "` satisfies the " STR(Concept) " concept, but should not."

#endif // K3_TOK3N_TESTS_COMMON_ASSERTS_CONCEPT_HPP
