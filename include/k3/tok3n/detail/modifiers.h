#pragma once
#include <k3/tok3n/detail/modifiers/apply_into.h>
#include <k3/tok3n/detail/modifiers/apply.h>
#include <k3/tok3n/detail/modifiers/complete.h>
#include <k3/tok3n/detail/modifiers/constant.h>
#include <k3/tok3n/detail/modifiers/defaulted.h>
#include <k3/tok3n/detail/modifiers/delimit.h>
#include <k3/tok3n/detail/modifiers/delimit_keep.h>
#include <k3/tok3n/detail/modifiers/exactly.h>
#include <k3/tok3n/detail/modifiers/ignore.h>
#include <k3/tok3n/detail/modifiers/into.h>
#include <k3/tok3n/detail/modifiers/join.h>
#include <k3/tok3n/detail/modifiers/map.h>
#include <k3/tok3n/detail/modifiers/multi.h>
#include <k3/tok3n/detail/modifiers/name.h>
#include <k3/tok3n/detail/modifiers/sub.h>

namespace k3::tok3n::detail {

constexpr auto operator%(parser auto p, modifier auto modifier)
requires requires { modifier(p); }
{
	return modifier(p);
}

template <modifier LHS, modifier RHS>
constexpr auto operator%(LHS, RHS)
{
	return multi_modifier<LHS, RHS>{};
}

template <modifier... LHS, modifier RHS>
constexpr auto operator%(multi_modifier<LHS...>, RHS)
{
	return multi_modifier<LHS..., RHS>{};
}

template <modifier LHS, modifier... RHS>
constexpr auto operator%(LHS, multi_modifier<RHS...>)
{
	return multi_modifier<LHS, RHS...>{};
}

template <modifier... LHS, modifier... RHS>
constexpr auto operator%(multi_modifier<LHS...>, multi_modifier<RHS...>)
{
	return multi_modifier<LHS..., RHS...>{};
}

} // namespace k3::tok3n::detail
