// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_ASSERTS_CONCEPT_HPP
#define K3_TOK3N_TESTS_COMMON_ASSERTS_CONCEPT_HPP

#include "framework/Assert.hpp"
#include <k3/tok3n/detail/parser.hpp>

#define ASSERT_CONCEPT(Concept, ...)                                             \
	ASSERT((Concept<__VA_ARGS__>),                                               \
		"`" STR(__VA_ARGS__) "` does not satisfy the " STR(Concept) " concept.")

#define ASSERT_NOT_CONCEPT(Concept, ...)                                                  \
	ASSERT(not (Concept<__VA_ARGS__>),                                                    \
		"`" STR(__VA_ARGS__) "` satisfies the " STR(Concept) " concept, but should not.")

#define ASSERT_IS_PARSER(P, V, PARSER_TYPE, ...)                            \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, P);                           \
	ASSERT(P::family == PARSER_TYPE,                                        \
		"`" STR(P) "::family` does not equal " STR(PARSER_TYPE));           \
	ASSERT((k3::tok3n::detail::parser_for<P, V>),                           \
		"`parser_for<" STR(P) ", " STR(V) ">` is not satisfied");           \
	ASSERT((std::same_as<typename P::template result_for<V>, __VA_ARGS__>), \
		"`" STR(P) "::result_for<" STR(V) ">` is not " STR(__VA_ARGS__))

#define ASSERT_IS_NOT_PARSER(P, V, PARSER_TYPE)                                   \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, P);                                 \
	ASSERT(P::family == PARSER_TYPE,                                              \
		"`" STR(P) "::family` does not equal " STR(PARSER_TYPE));                 \
	ASSERT(not (k3::tok3n::detail::parser_for<P, V>),                             \
		"`parser_for<" STR(P) ", " STR(V) ">` is satisfied but it should not be");

#define ASSERT_PARSER_VALUE_TYPE(P, V)                         \
	ASSERT((std::same_as<typename P::value_type, V>),          \
		"`" STR(P) "::result_for<" STR(V) ">` is not " STR(V))

#endif // K3_TOK3N_TESTS_COMMON_ASSERTS_CONCEPT_HPP
