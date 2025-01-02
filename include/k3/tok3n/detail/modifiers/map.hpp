// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_MAP_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_MAP_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/parsers/map.hpp>

namespace k3::tok3n::detail {

template <auto function>
struct map_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::map;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return map_parser<P, integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIERS_MAP_HPP
