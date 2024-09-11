#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/Defaulted.h>

namespace k3::tok3n::modifiers {

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::defaulted;

	template <k3::tok3n::detail::parser P>
	constexpr auto operator()(P) const
	{
		return aliases::Defaulted<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
