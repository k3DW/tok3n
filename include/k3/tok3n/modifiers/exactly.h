#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/repeat/Exactly.h>

namespace k3::tok3n::modifiers {

template <std::size_t N>
requires (N != 0)
struct exactly final : ModifierBase
{
	static constexpr auto family = ModifierFamily::exactly;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return Exactly<P, detail::index_c<N>>{};
	}
};

} // namespace k3::tok3n::modifiers
