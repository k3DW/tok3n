#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct map final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::map;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return Map<P, detail::integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::modifiers
