#pragma once

#define ASSERT_CONCEPT(Concept, ...)                                     \
	ASSERT(Concept<__VA_ARGS__>,                                         \
		"(" #__VA_ARGS__ ") does not satisfy the " #Concept " concept.")

#define ASSERT_CONCEPT_PARSER(P) \
	ASSERT_CONCEPT(Parser, P)

#define ASSERT_CONCEPT_MODIFIER(M) \
	ASSERT_CONCEPT(Modifier, M)

#define ASSERT_IS_PARSER(P, PARSER_TYPE, ...)                                         \
	do {                                                                              \
		ASSERT_CONCEPT_PARSER(P);                                                     \
		ASSERT(P::type == PARSER_TYPE,                                                \
			"(" #P "::type) does not equal " #PARSER_TYPE);                           \
		ASSERT((std::same_as<typename P::result_type, __VA_ARGS__>),                  \
			"(" #P "::result_type) is not " #__VA_ARGS__);                            \
		ASSERT((IsParser<P, PARSER_TYPE, __VA_ARGS__>),                               \
			"IsParser<" #P ", " #PARSER_TYPE ", " #__VA_ARGS__ "> is not satisfied"); \
	} while(false)
