#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/static_array.h>
#include <k3/tok3n/parsers/adaptor/Named.h>
#include <k3/tok3n/modifiers/name.h>

namespace k3::tok3n::modifiers {

namespace detail {

template <class T, k3::tok3n::detail::substitution Sub>
requires (not k3::tok3n::detail::parser<T>)
constexpr auto SubstituteOne(T, Sub)
	-> T;

template <template <k3::tok3n::detail::static_array> class Basic, k3::tok3n::detail::static_array arr, k3::tok3n::detail::substitution Sub>
requires k3::tok3n::detail::parser<Basic<arr>>
constexpr auto SubstituteOne(Basic<arr>, Sub)
	-> Basic<arr>;

template <k3::tok3n::detail::parser P, k3::tok3n::detail::static_array str, k3::tok3n::detail::substitution Sub>
constexpr k3::tok3n::detail::parser auto SubstituteOne(Named<P, str>, Sub);

template <template <class...> class Template, class... Args, k3::tok3n::detail::substitution Sub>
requires k3::tok3n::detail::parser<Template<Args...>>
constexpr k3::tok3n::detail::parser auto SubstituteOne(Template<Args...>, Sub)
{
	return Template<decltype(SubstituteOne(Args{}, Sub{}))...>{};
}

template <k3::tok3n::detail::parser P, k3::tok3n::detail::static_array str, k3::tok3n::detail::substitution Sub>
constexpr k3::tok3n::detail::parser auto SubstituteOne(Named<P, str>, Sub)
{
	using InnerSubbed = decltype(SubstituteOne(P{}, Sub{}));
	if constexpr (Sub::name == str)
		return Sub::mod(InnerSubbed{});
	else
		return Named<InnerSubbed, str>{};
}

template <k3::tok3n::detail::parser P, k3::tok3n::detail::substitution Sub, k3::tok3n::detail::substitution... Subs>
constexpr k3::tok3n::detail::parser auto Substitute(P, Sub, Subs...)
{
	using Subbed = decltype(SubstituteOne(P{}, Sub{}));
	if constexpr (sizeof...(Subs) == 0)
		return Subbed{};
	else
		return decltype(Substitute(Subbed{}, Subs{}...)){};
}

} // namespace detail

struct sub final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::sub;

	template <k3::tok3n::detail::parser P, k3::tok3n::detail::substitution Sub, k3::tok3n::detail::substitution... Subs>
	constexpr auto operator()(P, Sub, Subs...) const
	{
		return decltype(detail::Substitute(P{}, Sub{}, Subs{}...)){};
	}

	template <k3::tok3n::detail::substitution Sub, k3::tok3n::detail::substitution... Subs>
	struct inner final : k3::tok3n::detail::modifier_base
	{
		static constexpr auto family = k3::tok3n::detail::modifier_family::sub;

		template <k3::tok3n::detail::parser P>
		constexpr auto operator()(P) const
		{
			return decltype(detail::Substitute(P{}, Sub{}, Subs{}...)){};
		}
	};

	template <k3::tok3n::detail::substitution Sub, k3::tok3n::detail::substitution... Subs>
	constexpr auto operator()(Sub, Subs...) const
	{
		return inner<Sub, Subs...>{};
	}
};

} // namespace k3::tok3n::modifiers
