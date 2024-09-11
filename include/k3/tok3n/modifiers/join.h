#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/Join.h>

namespace k3::tok3n::modifiers {

struct join final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::join;

	template <k3::tok3n::detail::parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == detail::join_family)
			return P{};
		else
			return Join<P>{};
	}
};

} // namespace k3::tok3n::modifiers
