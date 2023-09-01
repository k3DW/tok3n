#pragma once
#include "framework/Assert.h"
#include <k3/tok3n/concepts/Parser.h>

#define ASSERT_CONCEPT(Concept, ...)                                             \
	ASSERT((Concept<__VA_ARGS__>),                                               \
		"`" STR(__VA_ARGS__) "` does not satisfy the " STR(Concept) " concept.")

#define ASSERT_NOT_CONCEPT(Concept, ...)                                                  \
	ASSERT(not (Concept<__VA_ARGS__>),                                                    \
		"`" STR(__VA_ARGS__) "` satisfies the " STR(Concept) " concept, but should not.")

#define ASSERT_IS_PARSER(P, PARSER_TYPE, ...)                                                  \
	ASSERT_CONCEPT(Parser, P);                                                                 \
	ASSERT(P::type == PARSER_TYPE,                                                             \
		"`" STR(P) "::type` does not equal " STR(PARSER_TYPE));                                \
	ASSERT((std::same_as<typename P::result_type, __VA_ARGS__>),                               \
		"`" STR(P) "::result_type` is not " STR(__VA_ARGS__));                                 \
	ASSERT((IsParser<P, PARSER_TYPE, __VA_ARGS__>),                                            \
		"`IsParser<" STR(P) ", " STR(PARSER_TYPE) ", " STR(__VA_ARGS__) ">` is not satisfied")
