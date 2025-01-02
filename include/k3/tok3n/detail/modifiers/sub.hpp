// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/modifiers/name.hpp>
#include <k3/tok3n/detail/static_array.hpp>
#include <k3/tok3n/detail/substitution.hpp>
#include <k3/tok3n/detail/parsers/named.hpp>

namespace k3::tok3n::detail {

namespace impl {

template <class T, substitution Sub>
struct substitute_one
{
	using type = T;
};

template <parser P, static_array str, substitution Sub>
requires (Sub::name == str)
struct substitute_one<named_parser<P, str>, Sub>
{
	using type = decltype(Sub::mod(typename substitute_one<P, Sub>::type{}));
};

template <parser P, static_array str, substitution Sub>
requires (Sub::name != str)
struct substitute_one<named_parser<P, str>, Sub>
{
	using type = named_parser<typename substitute_one<P, Sub>::type, str>;
};

template <template <class...> class Template, class... Args, substitution Sub>
struct substitute_one<Template<Args...>, Sub>
{
	using type = Template<typename substitute_one<Args, Sub>::type...>;
};

template <parser P, substitution Sub, substitution... Subs>
constexpr parser auto substitute(P, Sub, Subs...)
{
	using Subbed = typename substitute_one<P, Sub>::type;
	if constexpr (sizeof...(Subs) == 0)
		return Subbed{};
	else
		return substitute(Subbed{}, Subs{}...);
}

} // namespace impl

struct sub_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::sub;

	template <parser P, substitution Sub, substitution... Subs>
	constexpr auto operator()(P, Sub, Subs...) const
	{
		return impl::substitute(P{}, Sub{}, Subs{}...);
	}

	template <substitution Sub, substitution... Subs>
	struct inner final : modifier_base
	{
		static constexpr auto family = modifier_family::sub;

		template <parser P>
		constexpr auto operator()(P) const
		{
			return impl::substitute(P{}, Sub{}, Subs{}...);
		}
	};

	template <substitution Sub, substitution... Subs>
	constexpr auto operator()(Sub, Subs...) const
	{
		return inner<Sub, Subs...>{};
	}
};

} // namespace k3::tok3n::detail
