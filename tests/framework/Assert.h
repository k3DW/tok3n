#pragma once

using namespace k3::tok3n;

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
