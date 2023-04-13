#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/repeat/Exactly.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <std::size_t N>
requires (N != 0)
struct exactly final : ModifierBase
{
	template <Parser P>
	requires constructible::Exactly<P, N>
	consteval auto operator()(P) const
	{
		return Exactly<P, N>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
