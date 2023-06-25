#pragma once
#include <k3/tok3n/namespace.h>

namespace k3::tok3n::tests {

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

} // namespace k3::tok3n::tests
