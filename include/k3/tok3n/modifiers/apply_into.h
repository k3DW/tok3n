#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/ApplyInto.h>

namespace k3::tok3n::modifiers {

template <class T>
struct apply_into final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return ApplyInto<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
