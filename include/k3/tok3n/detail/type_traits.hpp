// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_TYPE_TRAITS_HPP
#define K3_TOK3N_DETAIL_TYPE_TRAITS_HPP

#include <concepts>
#include <tuple>
#include <type_traits>
#include <variant>

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



template <class P, class T>
concept pointer_of =
	std::is_pointer_v<P> and
	std::same_as<std::remove_cvref_t<decltype(*P{})>, T>;



// Extend `std::invoke_result` to allow `<F,void>` to mean just `<F>`
template <class F, class... Args>
struct invoke_result_ex : std::invoke_result<F, Args...> {};
template <class F>
struct invoke_result_ex<F, void> : std::invoke_result<F> {};
template <class F>
struct invoke_result_ex<F, const void> : std::invoke_result<F> {};
template <class F, class... Args>
using invoke_result_ex_t = typename invoke_result_ex<F, Args...>::type;

template <class T, class F, class... Args>
concept invoke_assignable_to =
	std::invocable<F, Args...> and
	std::is_assignable_v<T, std::invoke_result_t<F, Args...>&&>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_TYPE_TRAITS_HPP
