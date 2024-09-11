#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/ApplyMap.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct apply final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::apply;

	template <k3::tok3n::detail::parser P>
	constexpr auto operator()(P) const
	{
		return aliases::ApplyMap<P, detail::integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::modifiers
