#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE(detail::modifiers)

template <auto function>
struct fn final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Transform<P, function>{};
	}
};

struct join final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (std::same_as<Input, typename P::result_type>)
			return P{};
		else
			return Join<P>{};
	}
};

template <class T>
struct into final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Into<P, T>{};
	}

	template <Parser... Ps>
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
struct defaulted final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Defaulted<P, T>{};
	}
};

template <std::size_t N>
struct exactly final
{
	template <Parser P>
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

struct delimit final
{
	template <Parser P, Parser D>
	consteval auto operator()(P, D) const
	{
		return Delimit<P, D>{};
	}

	template <Parser D>
	struct inner final
	{
		template <Parser P>
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

TOK3N_END_NAMESPACE(detail::modifiers)



TOK3N_BEGIN_NAMESPACE()

template <auto function> constexpr auto fn        = detail::modifiers::fn<function>{};
                         constexpr auto join      = detail::modifiers::join{};
template <class T>       constexpr auto into      = detail::modifiers::into<T>{};
template <auto value>    constexpr auto constant  = detail::modifiers::constant<value>{};
template <class T>       constexpr auto defaulted = detail::modifiers::defaulted<T>{};
template <std::size_t N> constexpr auto exactly   = detail::modifiers::exactly<N>{};
                         constexpr auto ignore    = detail::modifiers::ignore{};
                         constexpr auto complete  = detail::modifiers::complete{};
                         constexpr auto delimit   = detail::modifiers::delimit{};

template <auto function> constexpr bool is_modifier_v<detail::modifiers::fn<function>>      = true;
template <>              constexpr bool is_modifier_v<detail::modifiers::join>              = true;
template <class T>       constexpr bool is_modifier_v<detail::modifiers::into<T>>           = true;
template <auto value>    constexpr bool is_modifier_v<detail::modifiers::constant<value>>   = true;
template <class T>       constexpr bool is_modifier_v<detail::modifiers::defaulted<T>>      = true;
template <std::size_t N> constexpr bool is_modifier_v<detail::modifiers::exactly<N>>        = true;
template <>              constexpr bool is_modifier_v<detail::modifiers::ignore>            = true;
template <>              constexpr bool is_modifier_v<detail::modifiers::complete>          = true;
template <Parser D>      constexpr bool is_modifier_v<detail::modifiers::delimit::inner<D>> = true;

consteval auto operator%(Parser auto p, Modifier auto modifier)
{
	return modifier(p);
}

TOK3N_END_NAMESPACE()
