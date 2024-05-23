#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/adaptor/Complete.h>

namespace k3::tok3n::modifiers {

struct complete final : ModifierBase
{
	static constexpr auto family = ModifierFamily::complete;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == CompleteFamily)
			return P{};
		else
			return Complete<P>{};
	}
};

} // namespace k3::tok3n::modifiers
