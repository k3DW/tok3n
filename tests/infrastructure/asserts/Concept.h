#pragma once
#include "infrastructure/framework/Assert.h"
#include <k3/tok3n/concepts/Parser.h>

#define ASSERT_CONCEPT(Concept, ...)                                             \
	ASSERT((Concept<__VA_ARGS__>),                                               \
		"`" STR(__VA_ARGS__) "` does not satisfy the " STR(Concept) " concept.")

#define ASSERT_NOT_CONCEPT(Concept, ...)                                                  \
	ASSERT(not (Concept<__VA_ARGS__>),                                                    \
		"`" STR(__VA_ARGS__) "` satisfies the " STR(Concept) " concept, but should not.")

#define ASSERT_IS_PARSER(P, V, PARSER_TYPE, ...)                                       \
	ASSERT_CONCEPT(Parser, P);                                                         \
	ASSERT(P::family == PARSER_TYPE,                                                   \
		"`" STR(P) "::family` does not equal " STR(PARSER_TYPE));                      \
	ASSERT((ParserFor<P, V, __VA_ARGS__>),                                             \
		"`ParserFor<" STR(P) ", " STR(V) ", " STR(__VA_ARGS__) ">` is not satisfied"); \
	ASSERT((std::same_as<typename P::template result_for<V>, __VA_ARGS__>),            \
		"`" STR(P) "::result_for<" STR(V) ">` is not " STR(__VA_ARGS__))

#define ASSERT_PARSER_VALUE_TYPE(P, V)                         \
	ASSERT((std::same_as<typename P::value_type, V>),          \
		"`" STR(P) "::result_for<" STR(V) ">` is not " STR(V))
