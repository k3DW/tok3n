#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/repeat/Exactly.h>

namespace k3::tok3n::modifiers {

template <std::size_t N>
requires (N != 0)
struct exactly final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::exactly;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return Exactly<P, detail::index_c<N>>{};
	}
};

} // namespace k3::tok3n::modifiers
