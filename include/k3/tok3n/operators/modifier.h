#pragma once
#include <k3/tok3n/modifiers.h>

TOK3N_BEGIN_NAMESPACE(inline operators)

template <auto function> constexpr auto apply        = modifiers::apply<function>{};
template <class T>       constexpr auto apply_into   = modifiers::apply_into<T>{};
                         constexpr auto complete     = modifiers::complete{};
template <auto value>    constexpr auto constant     = modifiers::constant<value>{};
template <class T>       constexpr auto defaulted    = modifiers::defaulted<T>{};
                         constexpr auto delimit      = modifiers::delimit{};
                         constexpr auto delimit_keep = modifiers::delimit_keep{};
template <std::size_t N> constexpr auto exactly      = modifiers::exactly<N>{};
template <auto function> constexpr auto fn           = modifiers::fn<function>{};
                         constexpr auto ignore       = modifiers::ignore{};
template <class T>       constexpr auto into         = modifiers::into<T>{};
template <class T>       constexpr auto into_choice  = modifiers::into_choice<T>{};
                         constexpr auto join         = modifiers::join{};

consteval auto operator%(Parser auto p, Modifier auto modifier)
requires requires { modifier(p); }
{
	return modifier(p);
}

template <Modifier LHS, Modifier RHS>
consteval auto operator%(LHS, RHS)
{
	return modifiers::multi<LHS, RHS>{};
}

template <Modifier... LHS, Modifier RHS>
consteval auto operator%(modifiers::multi<LHS...>, RHS)
{
	return modifiers::multi<LHS..., RHS>{};
}

template <Modifier LHS, Modifier... RHS>
consteval auto operator%(LHS, modifiers::multi<RHS...>)
{
	return modifiers::multi<LHS, RHS...>{};
}

template <Modifier... LHS, Modifier... RHS>
consteval auto operator%(modifiers::multi<LHS...>, modifiers::multi<RHS...>)
{
	return modifiers::multi<LHS..., RHS...>{};
}

TOK3N_END_NAMESPACE(inline operators)
