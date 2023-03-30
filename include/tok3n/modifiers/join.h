#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/divergent/Join.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

struct join final : ModifierBase
{
	template <Parser P>
	requires constructible::Join<P>
	consteval auto operator()(P) const
	{
		if constexpr (std::same_as<Input, typename P::result_type>)
			return P{};
		else
			return Join<P>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
