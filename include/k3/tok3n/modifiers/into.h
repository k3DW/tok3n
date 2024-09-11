#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/Into.h>

namespace k3::tok3n::modifiers {

template <class T>
struct into final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::into;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return aliases::Into<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
