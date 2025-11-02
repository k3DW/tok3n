// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_ASSERTS_PARSE_HPP
#define K3_TOK3N_TESTS_COMMON_ASSERTS_PARSE_HPP

#include "framework/assert.hpp"
#include <k3/tok3n/detail/parser.hpp>

#define IDENTITY(...) __VA_ARGS__
#define STR(...) #__VA_ARGS__

#define ASSERT_PARSE_IMPL_PARSE_VALID_(P, INPUT)                                              \
    ASSERT((P::parse(INPUT)).has_value())                                                     \
        << "`" STR(P) "::parse(" STR(INPUT) ")` does not give a valid result, but it should."

#define ASSERT_PARSE_IMPL_PARSE_INVALID_(P, INPUT)                                        \
    ASSERT(not (P::parse(INPUT)).has_value())                                             \
        << "`" STR(P) "::parse(" STR(INPUT) ")` gives a valid result, but it should not."

#define ASSERT_PARSE_IMPL_PARSE_RESULT_(P, INPUT, OUTPUT)                            \
    ASSERT(*(P::parse(INPUT)) == (OUTPUT))                                           \
        << "`*(" STR(P) "::parse(" STR(INPUT) "))` does not equal `" STR(OUTPUT) "`"

#define ASSERT_PARSE_IMPL_PARSE_REMAINING_(P, INPUT, REMAINING)                                  \
    ASSERT((P::parse(INPUT)).remaining() == (REMAINING))                                         \
        << "`" STR(P) "::parse(" STR(INPUT) ").remaining()` does not equal `" STR(REMAINING) "`"

#define ASSERT_PARSE_IMPL_LOOKAHEAD_VALID_(P, INPUT)                                              \
    ASSERT((P::lookahead(INPUT)).has_value())                                                     \
        << "`" STR(P) "::lookahead(" STR(INPUT) ")` does not give a valid result, but it should."

#define ASSERT_PARSE_IMPL_LOOKAHEAD_INVALID_(P, INPUT)                                        \
    ASSERT(not (P::lookahead(INPUT)).has_value())                                             \
        << "`" STR(P) "::lookahead(" STR(INPUT) ")` gives a valid result, but it should not."

#define ASSERT_PARSE_IMPL_LOOKAHEAD_REMAINING_(P, INPUT, REMAINING)                                  \
    ASSERT((P::lookahead(INPUT)).remaining() == (REMAINING))                                         \
        << "`" STR(P) "::lookahead(" STR(INPUT) ").remaining()` does not equal `" STR(REMAINING) "`"



#define ASSERT_PARSE_SUCCESS(P, INPUT, OUTPUT, REMAINING)       \
    ASSERT_PARSE_IMPL_PARSE_VALID_(P, INPUT);                   \
    ASSERT_PARSE_IMPL_PARSE_RESULT_(P, INPUT, OUTPUT);          \
    ASSERT_PARSE_IMPL_PARSE_REMAINING_(P, INPUT, REMAINING);    \
    ASSERT_PARSE_IMPL_LOOKAHEAD_VALID_(P, INPUT);               \
    ASSERT_PARSE_IMPL_LOOKAHEAD_REMAINING_(P, INPUT, REMAINING)

#define ASSERT_PARSE_SUCCESS_VOID(P, INPUT, REMAINING)          \
    ASSERT_PARSE_IMPL_PARSE_VALID_(P, INPUT);                   \
    ASSERT_PARSE_IMPL_PARSE_REMAINING_(P, INPUT, REMAINING);    \
    ASSERT_PARSE_IMPL_LOOKAHEAD_VALID_(P, INPUT);               \
    ASSERT_PARSE_IMPL_LOOKAHEAD_REMAINING_(P, INPUT, REMAINING)

#define ASSERT_PARSE_FAILURE(P, INPUT)                      \
    ASSERT_PARSE_IMPL_PARSE_INVALID_(P, INPUT);             \
    ASSERT_PARSE_IMPL_PARSE_REMAINING_(P, INPUT, INPUT);    \
    ASSERT_PARSE_IMPL_LOOKAHEAD_INVALID_(P, INPUT);         \
    ASSERT_PARSE_IMPL_LOOKAHEAD_REMAINING_(P, INPUT, INPUT)

#define ASSERT_PARSE_LOOKAHEAD_ONLY(P, INPUT, REMAINING)        \
    ASSERT_PARSE_IMPL_PARSE_INVALID_(P, INPUT);                 \
    ASSERT_PARSE_IMPL_PARSE_REMAINING_(P, INPUT, INPUT);        \
    ASSERT_PARSE_IMPL_LOOKAHEAD_VALID_(P, INPUT);               \
    ASSERT_PARSE_IMPL_LOOKAHEAD_REMAINING_(P, INPUT, REMAINING)

#endif // K3_TOK3N_TESTS_COMMON_ASSERTS_PARSE_HPP
