#pragma once
#include <k3/tok3n/modifiers.h>

namespace k3::tok3n {

template <auto function> inline constexpr auto apply        = modifiers::apply<function>{};
template <class T>       inline constexpr auto apply_into   = modifiers::apply_into<T>{};
                         inline constexpr auto complete     = modifiers::complete{};
template <auto value>    inline constexpr auto constant     = modifiers::constant<value>{};
template <class T>       inline constexpr auto defaulted    = modifiers::defaulted<T>{};
                         inline constexpr auto delimit      = modifiers::delimit{};
                         inline constexpr auto delimit_keep = modifiers::delimit_keep{};
template <std::size_t N> inline constexpr auto exactly      = modifiers::exactly<N>{};
template <auto function> inline constexpr auto fn           = modifiers::fn<function>{};
                         inline constexpr auto ignore       = modifiers::ignore{};
template <class T>       inline constexpr auto into         = modifiers::into<T>{};
                         inline constexpr auto join         = modifiers::join{};
template <StaticArray s> inline constexpr auto name         = modifiers::name<s>{};
                         inline constexpr auto sub          = modifiers::sub{};

constexpr auto operator%(Parser auto p, Modifier auto modifier)
requires requires { modifier(p); }
{
	return modifier(p);
}

template <Modifier LHS, Modifier RHS>
constexpr auto operator%(LHS, RHS)
{
	return modifiers::multi<LHS, RHS>{};
}

template <Modifier... LHS, Modifier RHS>
constexpr auto operator%(modifiers::multi<LHS...>, RHS)
{
	return modifiers::multi<LHS..., RHS>{};
}

template <Modifier LHS, Modifier... RHS>
constexpr auto operator%(LHS, modifiers::multi<RHS...>)
{
	return modifiers::multi<LHS, RHS...>{};
}

template <Modifier... LHS, Modifier... RHS>
constexpr auto operator%(modifiers::multi<LHS...>, modifiers::multi<RHS...>)
{
	return modifiers::multi<LHS..., RHS...>{};
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::apply;
using ::k3::tok3n::apply_into;
using ::k3::tok3n::complete;
using ::k3::tok3n::constant;
using ::k3::tok3n::defaulted;
using ::k3::tok3n::delimit;
using ::k3::tok3n::delimit_keep;
using ::k3::tok3n::exactly;
using ::k3::tok3n::fn;
using ::k3::tok3n::ignore;
using ::k3::tok3n::into;
using ::k3::tok3n::join;
using ::k3::tok3n::operator%;

} // namespace k3::tok3n::operators
