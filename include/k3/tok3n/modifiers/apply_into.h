#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/ApplyInto.h>

namespace k3::tok3n::modifiers {

template <class T>
struct apply_into final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::apply_into;

	template <k3::tok3n::detail::parser P>
	constexpr auto operator()(P) const
	{
		return aliases::ApplyInto<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
