#pragma once

using namespace k3::tok3n;

struct assert_t final {};

consteval assert_t operator,(assert_t self, bool b)
{
	if (!b)
		throw;
	return self;
}

constexpr auto assert = assert_t{};



// #define DISABLE_STATIC_ASSERT

#ifdef DISABLE_STATIC_ASSERT
#define STATIC_ASSERT(...)
#else
#define STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#endif

#define ASSERT(CONDITION, MESSAGE)             \
	[&]() -> bool {                            \
		STATIC_ASSERT((CONDITION), MESSAGE);   \
		return Assert((CONDITION), (MESSAGE)); \
	}()



#define ASSERT_PARSER_CONCEPT(P)                         \
	ASSERT(Parser<P>,                                    \
		"(" #P ") does not satisfy the Parser concept.")

#define ASSERT_IS_PARSER(P, PARSER_TYPE, ...)                                         \
	do {                                                                              \
		ASSERT_PARSER_CONCEPT(P);                                                     \
		ASSERT(P::type == PARSER_TYPE,                                                \
			"(" #P "::type) does not equal " #PARSER_TYPE);                           \
		ASSERT((std::same_as<typename P::result_type, __VA_ARGS__>),                  \
			"(" #P "::result_type) is not " #__VA_ARGS__);                            \
		ASSERT((IsParser<P, PARSER_TYPE, __VA_ARGS__>),                               \
			"IsParser<" #P ", " #PARSER_TYPE ", " #__VA_ARGS__ "> is not satisfied"); \
	} while(false)



#define TOK3N_ASSERT_P(condition, message) \
	do {                                   \
		if constexpr (not (condition))     \
			typename P::__error_with_type; \
	} while(false)

#define TOK3N_ASSERT_P2(condition, message)      \
	do {                                         \
		if constexpr (not (condition))           \
		{                                        \
			typename LHS::__error_with_type_LHS; \
			typename RHS::__error_with_type_RHS; \
		}                                        \
	} while(false)
