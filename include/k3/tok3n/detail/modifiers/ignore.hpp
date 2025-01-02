// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_IGNORE_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_IGNORE_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/parsers/ignore.hpp>

namespace k3::tok3n::detail {

struct ignore_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::ignore;

	template <parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == ignore_family)
			return P{};
		else
			return ignore_parser<P>{};
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIERS_IGNORE_HPP
