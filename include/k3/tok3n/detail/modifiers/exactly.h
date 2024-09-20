#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parsers/exactly.h>

namespace k3::tok3n::detail {

template <std::size_t N>
requires (N != 0)
struct exactly_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::exactly;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return exactly_parser<P, index_c<N>>{};
	}
};

} // namespace k3::tok3n::detail