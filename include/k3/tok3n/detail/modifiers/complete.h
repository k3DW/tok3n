#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parsers/complete.h>

namespace k3::tok3n::detail {

struct complete_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::complete;

	template <parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == complete_family)
			return P{};
		else
			return complete_parser<P>{};
	}
};

} // namespace k3::tok3n::detail
