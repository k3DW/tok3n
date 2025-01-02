// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPERATORS_MODIFIER_HPP
#define K3_TOK3N_DETAIL_OPERATORS_MODIFIER_HPP

#include <k3/tok3n/detail/modifiers/multi.hpp>

namespace k3::tok3n::detail {

namespace impl {

template <parser P, modifier M>
constexpr auto modifier_operator(P, M)
requires requires { M{}(P{}); }
{
	return M{}(P{});
}

template <modifier LHS, modifier RHS>
constexpr auto modifier_operator(LHS, RHS)
{
	return multi_modifier<LHS, RHS>{};
}

template <modifier... LHS, modifier RHS>
constexpr auto modifier_operator(multi_modifier<LHS...>, RHS)
{
	return multi_modifier<LHS..., RHS>{};
}

template <modifier LHS, modifier... RHS>
constexpr auto modifier_operator(LHS, multi_modifier<RHS...>)
{
	return multi_modifier<LHS, RHS...>{};
}

template <modifier... LHS, modifier... RHS>
constexpr auto modifier_operator(multi_modifier<LHS...>, multi_modifier<RHS...>)
{
	return multi_modifier<LHS..., RHS...>{};
}

} // namespace impl

template <class LHS, class RHS>
constexpr auto operator%(LHS, RHS)
requires requires { impl::modifier_operator(LHS{}, RHS{}); }
{
	return impl::modifier_operator(LHS{}, RHS{});
}

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPERATORS_MODIFIER_HPP
