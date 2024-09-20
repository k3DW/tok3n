#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/aliases/into.h>

namespace k3::tok3n::detail {

template <class T>
struct into_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::into;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return into_parser<P, T>{};
	}
};

} // namespace k3::tok3n::detail