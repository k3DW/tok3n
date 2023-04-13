#pragma once
#include <tok3n/namespace.h>

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

TOK3N_END_NAMESPACE(tests)
