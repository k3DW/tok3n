#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/repeat/Delimit.h>

namespace k3::tok3n::modifiers {

struct delimit_keep final : ModifierBase
{
	static constexpr auto family = ModifierFamily::delimit_keep;

	template <Parser P, ParserCompatibleWith<P> D>
	constexpr auto operator()(P, D) const
	{
		return Delimit<P, D, True>{};
	}

	template <Parser D>
	struct inner final : ModifierBase
	{
		static constexpr auto family = ModifierFamily::delimit_keep;

		template <ParserCompatibleWith<D> P>
		constexpr auto operator()(P) const
		{
			return Delimit<P, D, True>{};
		}
	};

	template <Parser D>
	constexpr auto operator()(D) const
	{
		return inner<D>{};
	}
};

} // namespace k3::tok3n::modifiers
