#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Defaulted.h>

namespace k3::tok3n::modifiers {

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted final : ModifierBase
{
	template <Parser P>
	constexpr auto operator()(P) const
	{
		return Defaulted<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
