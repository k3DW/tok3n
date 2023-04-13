#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/divergent/Into.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <class T>
struct into final : ModifierBase
{
	template <Parser P>
	requires constructible::Into<P, T>
	consteval auto operator()(P) const
	{
		return Into<P, T>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
