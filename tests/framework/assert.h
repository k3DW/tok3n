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
