// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_INTO_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_INTO_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/aliases/into.hpp>

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

#endif // K3_TOK3N_DETAIL_MODIFIERS_INTO_HPP
