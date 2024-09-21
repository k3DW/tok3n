#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parsers/join.h>

namespace k3::tok3n::detail {

struct join_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::join;

	template <parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == join_family)
			return P{};
		else
			return join_parser<P>{};
	}
};

} // namespace k3::tok3n::detail
