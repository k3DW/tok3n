#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/adaptor/Complete.h>

namespace k3::tok3n::modifiers {

struct complete final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (P::type == CompleteFamily)
			return P{};
		else
			return Complete<P>{};
	}
};

} // namespace k3::tok3n::modifiers
