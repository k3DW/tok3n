#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/aliases/defaulted.h>

namespace k3::tok3n::detail {

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::defaulted;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return defaulted_parser<P, T>{};
	}
};

} // namespace k3::tok3n::detail
