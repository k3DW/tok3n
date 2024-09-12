#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/adaptor/Complete.h>

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
			return Complete<P>{};
	}
};

} // namespace k3::tok3n::detail
