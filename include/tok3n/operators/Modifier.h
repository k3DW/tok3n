#pragma once
#include <tok3n/modifiers.h>

TOK3N_BEGIN_NAMESPACE(detail::modifiers)

template <auto function>
struct apply final : ModifierBase
{
	template <Parser P>
	requires detail::ApplyTransform_able<P, function>
	consteval auto operator()(P) const
	{
		return ApplyTransform<P, function>{};
	}
};

template <class T>
struct into final : ModifierBase
{
	template <Parser P>
	requires detail::Into_able<P, T>
	consteval auto operator()(P) const
	{
		return Into<P, T>{};
	}
};

template <class T>
struct apply_into final : ModifierBase
{
	template <Parser P>
	requires detail::ApplyInto_able<P, T>
	consteval auto operator()(P) const
	{
		return ApplyInto<P, T>{};
	}
};

template <class T>
struct into_choice final : ModifierBase
{
	template <Parser... Ps>
	requires (... && detail::Into_able<Ps, T>) && (detail::Choice_able<Into<Ps, T>...>)
	consteval auto operator()(Ps...) const
	{
		return Choice<Into<Ps, T>...>{};
	}
};

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

                         constexpr auto complete    = modifiers::complete{};
                         constexpr auto delimit     = modifiers::delimit{};
template <std::size_t N> constexpr auto exactly     = modifiers::exactly<N>{};
template <auto function> constexpr auto fn          = modifiers::fn<function>{};
                         constexpr auto ignore      = modifiers::ignore{};
                         constexpr auto join        = modifiers::join{};
template <auto function> constexpr auto apply       = detail::modifiers::apply<function>{};
template <class T>       constexpr auto into        = detail::modifiers::into<T>{};
template <class T>       constexpr auto apply_into  = detail::modifiers::apply_into<T>{};
template <class T>       constexpr auto into_choice = detail::modifiers::into_choice<T>{};
template <auto value>    constexpr auto constant    = detail::modifiers::constant<value>{};
template <class T>       constexpr auto defaulted   = detail::modifiers::defaulted<T>{};

consteval auto operator%(Parser auto p, Modifier auto modifier)
requires requires { modifier(p); }
{
	return modifier(p);
}

}

TOK3N_END_NAMESPACE()
