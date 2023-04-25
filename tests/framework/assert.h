#pragma once
#include <k3/tok3n/namespace.h>

TOK3N_BEGIN_NAMESPACE(tests)

namespace detail
{

	struct assert final {};

	consteval assert operator,(assert self, bool b)
	{
		if (!b)
			throw;
		return self;
	}

}

constexpr auto assert = detail::assert{};

#define TOK3N_ASSERT_P(condition, message) \
	do {                                   \
		if constexpr (not (condition))     \
			typename P::__error_with_type; \
	} while(false)

TOK3N_END_NAMESPACE(tests)
