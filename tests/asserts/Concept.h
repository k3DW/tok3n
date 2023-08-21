#pragma once
#include "framework/Assert.h"
#include <k3/tok3n/concepts/Parser.h>

#define ASSERT_CONCEPT(Concept, ...)                                     \
	ASSERT(Concept<__VA_ARGS__>,                                         \
		"`" #__VA_ARGS__ "` does not satisfy the " #Concept " concept.")

#define ASSERT_IS_PARSER(P, PARSER_TYPE, ...)                                      \
	ASSERT_CONCEPT(Parser, P);                                                     \
	ASSERT(P::type == PARSER_TYPE,                                                 \
		"`" #P "::type` does not equal " #PARSER_TYPE);                            \
	ASSERT((std::same_as<typename P::result_type, __VA_ARGS__>),                   \
		"`" #P "::result_type` is not " #__VA_ARGS__);                             \
	ASSERT((IsParser<P, PARSER_TYPE, __VA_ARGS__>),                                \
		"`IsParser<" #P ", " #PARSER_TYPE ", " #__VA_ARGS__ ">` is not satisfied")
