#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/adaptor/Delimit.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

struct delimit final
{
	template <Parser P, Parser D>
	requires detail::Delimit_able<P, D>
	consteval auto operator()(P, D) const
	{
		return Delimit<P, D>{};
	}

	template <Parser D>
	struct inner final : ModifierBase
	{
		template <Parser P>
		requires detail::Delimit_able<P, D>
		consteval auto operator()(P) const
		{
			return Delimit<P, D>{};
		}
	};

	template <Parser D>
	consteval auto operator()(D) const
	{
		return inner<D>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
