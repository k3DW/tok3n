#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Join.h>

namespace k3::tok3n::modifiers {

struct join final : ModifierBase
{
	static constexpr auto family = ModifierFamily::join;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == JoinFamily)
			return P{};
		else
			return Join<P>{};
	}
};

} // namespace k3::tok3n::modifiers
