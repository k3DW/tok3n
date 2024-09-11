#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/Constant.h>

namespace k3::tok3n::modifiers {

template <auto value>
struct constant final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::constant;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return aliases::Constant<P, detail::integral_constant<value>>{};
	}
};

} // namespace k3::tok3n::modifiers
