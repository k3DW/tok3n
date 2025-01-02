// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_BASIC_HPP
#define K3_TOK3N_BASIC_HPP

#include <k3/tok3n/detail/parsers/any_of.hpp>
#include <k3/tok3n/detail/parsers/none_of.hpp>
#include <k3/tok3n/detail/parsers/all_of.hpp>
#include <k3/tok3n/detail/parsers/ignore.hpp>

namespace k3::tok3n {

template <detail::static_array arr>
constexpr auto any = detail::any_of_parser<detail::sort_and_unique<arr>()>{};

template <auto t, auto... ts>
requires (... and std::constructible_from<std::remove_cvref_t<decltype(t)>, decltype(ts)>)
constexpr auto any_of = any<detail::static_array<std::remove_cvref_t<decltype(t)>, 1 + sizeof...(ts)>{ t, ts... }>;

template <detail::static_array arr>
constexpr auto none = detail::none_of_parser<detail::sort_and_unique<arr>()>{};

template <auto t, auto... ts>
requires (... and std::constructible_from<std::remove_cvref_t<decltype(t)>, decltype(ts)>)
constexpr auto none_of = none<detail::static_array<std::remove_cvref_t<decltype(t)>, 1 + sizeof...(ts)>{ t, ts... }>;

template <detail::static_array arr>
constexpr auto all = detail::all_of_parser<arr>{};

template <auto t, auto... ts>
requires (... and std::constructible_from<std::remove_cvref_t<decltype(t)>, decltype(ts)>)
constexpr auto all_of = all<detail::static_array<std::remove_cvref_t<decltype(t)>, 1 + sizeof...(ts)>{ t, ts... }>;

template <detail::static_array arr>
constexpr auto ign = detail::ignore_parser<detail::all_of_parser<arr>>{};



template <detail::static_array arr>
consteval auto operator"" _any()
{
	return any<arr>;
}

template <detail::static_array arr>
consteval auto operator"" _any_of()
{
	return any<arr>;
}

template <detail::static_array arr>
consteval auto operator"" _none()
{
	return none<arr>;
}

template <detail::static_array arr>
consteval auto operator"" _none_of()
{
	return none<arr>;
}

template <detail::static_array arr>
consteval auto operator"" _all()
{
	return all<arr>;
}

template <detail::static_array arr>
consteval auto operator"" _all_of()
{
	return all<arr>;
}

template <detail::static_array arr>
consteval auto operator"" _ign()
{
	return ign<arr>;
}

} // namespace k3::tok3n

#endif // K3_TOK3N_BASIC_HPP
