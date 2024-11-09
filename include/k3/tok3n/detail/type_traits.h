// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <concepts>
#include <type_traits>

namespace k3::tok3n::detail {

template <class T>
concept character = // https://en.cppreference.com/w/cpp/language/types
	std::same_as<std::remove_const_t<T>, signed char>   or
	std::same_as<std::remove_const_t<T>, unsigned char> or
	std::same_as<std::remove_const_t<T>, char>          or
	std::same_as<std::remove_const_t<T>, wchar_t>       or
	std::same_as<std::remove_const_t<T>, char16_t>      or
	std::same_as<std::remove_const_t<T>, char32_t>      or
	std::same_as<std::remove_const_t<T>, char8_t>;

template <class T, class U>
concept equality_comparable_with = // `std::equality_comparable_with` requires a common reference
	requires (T t, U u) { { t == u } -> std::convertible_to<bool>; };

template <class T>
concept implicitly_default_constructible = requires (void(f)(T)) { f({}); };



template <auto value>
using integral_constant = std::integral_constant<std::remove_const_t<decltype(value)>, value>;

template <std::size_t N>
using index_c = integral_constant<N>;

template <class value_type, auto value>
concept constexpr_value = std::same_as<std::remove_const_t<decltype(value)>, value_type>;

template <class T>
concept is_integral_constant =
	requires { typename T::value_type; } and
	constexpr_value<typename T::value_type, T{}.operator typename T::value_type()> and
	constexpr_value<typename T::value_type, T{}()> and
	constexpr_value<typename T::value_type, T::value>;

template <class T, class value_type>
concept integral_constant_of =
	is_integral_constant<T> and
	std::same_as<value_type, typename T::value_type>;



template <class E, E e, E lower, E upper>
concept enum_within_bounds =
	std::is_enum_v<E> and
	static_cast<std::underlying_type_t<E>>(e) > static_cast<std::underlying_type_t<E>>(lower) and
	static_cast<std::underlying_type_t<E>>(e) < static_cast<std::underlying_type_t<E>>(upper);



namespace impl {

template <bool Value, class Type>
struct unwrap_if_single_trait
{
	static constexpr bool unwrapped = Value;
	using type = Type;
};

template <template <class...> class List>
consteval auto unwrap_if_single(List<>) -> unwrap_if_single_trait<true, void>;

template <template <class...> class List, class T>
consteval auto unwrap_if_single(List<T>) -> unwrap_if_single_trait<true, T>;

template <template <class...> class List, class... Ts>
consteval auto unwrap_if_single(List<Ts...>) -> unwrap_if_single_trait<false, List<Ts...>>;

} // namespace impl

template <class List>
using unwrap_if_single = decltype(impl::unwrap_if_single(List{}));



template <class P, class T>
concept pointer_of =
	std::is_pointer_v<P> and
	std::same_as<std::remove_cvref_t<decltype(*P{})>, T>;

template <class T>
concept span_like = requires (T& t, const T& ct)
	{
		typename T::value_type;
		{ ct.data() } -> pointer_of<typename T::value_type>; // `data()` could return a pointer-to-const or pointer-to-non-const
		{ ct.size() } -> std::same_as<std::size_t>;
		{ ct.empty() } -> std::same_as<bool>;
		t = T{};
		t = T{ ct.data(), ct.size() };
	};

} // namespace k3::tok3n::detail
