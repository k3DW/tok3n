#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/repeat/Delimit.h>

namespace k3::tok3n::modifiers {

struct delimit_keep final
{
	template <Parser P, Parser D>
	requires DelimitConstructible<P, D, std::true_type>
	consteval auto operator()(P, D) const
	{
		return Delimit<P, D, std::true_type>{};
	}

	template <Parser D>
	struct inner final : ModifierBase
	{
		template <Parser P>
		requires DelimitConstructible<P, D, std::true_type>
		consteval auto operator()(P) const
		{
			return Delimit<P, D, std::true_type>{};
		}
	};

	template <Parser D>
	consteval auto operator()(D) const
	{
		return inner<D>{};
	}
};

} // namespace k3::tok3n::modifiers
