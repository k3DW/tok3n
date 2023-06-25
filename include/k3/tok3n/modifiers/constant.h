#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Constant.h>

namespace k3::tok3n::modifiers {

template <auto value>
struct constant final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Constant<P, value>{};
	}
};

} // namespace k3::tok3n::modifiers
