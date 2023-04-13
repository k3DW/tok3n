#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/adaptor/Complete.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

struct complete final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (P::type == CompleteType)
			return P{};
		else
			return Complete<P>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
