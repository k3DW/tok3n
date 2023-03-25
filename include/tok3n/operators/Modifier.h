#pragma once
#include <tok3n/modifiers.h>

TOK3N_BEGIN_NAMESPACE(detail::modifiers)

template <auto value>
struct constant final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Constant<P, value>{};
	}
};

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Defaulted<P, T>{};
	}
};

TOK3N_END_NAMESPACE(detail::modifiers)



TOK3N_BEGIN_NAMESPACE()

inline namespace operators
{

template <auto function> constexpr auto apply       = modifiers::apply<function>{};
template <class T>       constexpr auto apply_into  = modifiers::apply_into<T>{};
                         constexpr auto complete    = modifiers::complete{};
                         constexpr auto delimit     = modifiers::delimit{};
template <std::size_t N> constexpr auto exactly     = modifiers::exactly<N>{};
template <auto function> constexpr auto fn          = modifiers::fn<function>{};
                         constexpr auto ignore      = modifiers::ignore{};
template <class T>       constexpr auto into        = modifiers::into<T>{};
template <class T>       constexpr auto into_choice = modifiers::into_choice<T>{};
                         constexpr auto join        = modifiers::join{};
template <auto value>    constexpr auto constant    = detail::modifiers::constant<value>{};
template <class T>       constexpr auto defaulted   = detail::modifiers::defaulted<T>{};

consteval auto operator%(Parser auto p, Modifier auto modifier)
requires requires { modifier(p); }
{
	return modifier(p);
}

}

TOK3N_END_NAMESPACE()
