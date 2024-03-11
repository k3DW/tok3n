#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Transform.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct fn final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Transform<P, Const<function>>{};
	}
};

} // namespace k3::tok3n::modifiers
