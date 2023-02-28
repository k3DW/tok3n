#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE(detail::modifiers)

template <std::size_t N>
requires (N != 0)
struct exactly final
{
	template <Parser P>
	requires detail::Exactly_able<P, N>
	consteval auto operator()(P) const
	{
		return Exactly<P, N>{};
	}
};

struct ignore final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (IsIgnore<P>)
			return P{};
		else
			return Ignore<P>{};
	}
};

struct delimit final
{
	template <Parser P, Parser D>
	requires detail::Delimit_able<P, D>
	consteval auto operator()(P, D) const
	{
		return Delimit<P, D>{};
	}

	template <Parser D>
	struct inner final
	{
		template <Parser P>
		requires detail::Delimit_able<P, D>
		consteval auto operator()(P) const
		{
			return Delimit<P, D>{};
		}
	};

	template <Parser D>
	consteval auto operator()(D) const
	{
		return inner<D>{};
	}
};

struct complete final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (IsComplete<P>)
			return P{};
		else
			return Complete<P>{};
	}
};

struct join final
{
	template <Parser P>
	requires detail::Join_able<P>
	consteval auto operator()(P) const
	{
		if constexpr (std::same_as<Input, typename P::result_type>)
			return P{};
		else
			return Join<P>{};
	}
};

template <auto function>
struct fn final
{
	template <Parser P>
	requires detail::Transform_able<P, function>
	consteval auto operator()(P) const
	{
		return Transform<P, function>{};
	}
};

template <class T>
struct into final
{
	template <Parser P>
	requires detail::Into_able<P, T>
	consteval auto operator()(P) const
	{
		return Into<P, T>{};
	}
};

template <class T>
struct apply_into final
{
	template <Parser P>
	requires detail::ApplyInto_able<P, T>
	consteval auto operator()(P) const
	{
		return ApplyInto<P, T>{};
	}
};

template <class T>
struct into_choice final
{
	template <Parser... Ps>
	requires (... && detail::Into_able<Ps, T>) && (detail::Choice_able<Into<Ps, T>...>)
	consteval auto operator()(Ps...) const
	{
		return Choice<Into<Ps, T>...>{};
	}
};

template <auto value>
struct constant final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Constant<P, value>{};
	}
};

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Defaulted<P, T>{};
	}
};

TOK3N_END_NAMESPACE(detail::modifiers)



TOK3N_BEGIN_NAMESPACE()

template <std::size_t N> constexpr bool is_modifier_v<detail::modifiers::exactly<N>> = true;
template <>              constexpr bool is_modifier_v<detail::modifiers::ignore> = true;
template <Parser D>      constexpr bool is_modifier_v<detail::modifiers::delimit::inner<D>> = true;
template <>              constexpr bool is_modifier_v<detail::modifiers::complete> = true;
template <>              constexpr bool is_modifier_v<detail::modifiers::join> = true;
template <auto function> constexpr bool is_modifier_v<detail::modifiers::fn<function>> = true;
template <class T>       constexpr bool is_modifier_v<detail::modifiers::into<T>> = true;
template <class T>       constexpr bool is_modifier_v<detail::modifiers::apply_into<T>> = true;
template <class T>       constexpr bool is_modifier_v<detail::modifiers::into_choice<T>> = true;
template <auto value>    constexpr bool is_modifier_v<detail::modifiers::constant<value>> = true;
template <class T>       constexpr bool is_modifier_v<detail::modifiers::defaulted<T>> = true;

inline namespace operators
{

template <std::size_t N> constexpr auto exactly     = detail::modifiers::exactly<N>{};
                         constexpr auto ignore      = detail::modifiers::ignore{};
                         constexpr auto delimit     = detail::modifiers::delimit{};
                         constexpr auto complete    = detail::modifiers::complete{};
                         constexpr auto join        = detail::modifiers::join{};
template <auto function> constexpr auto fn          = detail::modifiers::fn<function>{};
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
