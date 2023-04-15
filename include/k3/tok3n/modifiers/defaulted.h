#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Defaulted.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Defaulted<P, T>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
