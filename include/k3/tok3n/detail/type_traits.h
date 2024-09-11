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
using integral_constant = std::integral_constant<decltype(value), value>;

template <std::size_t N>
using index_c = integral_constant<N>;

template <class value_type, auto value>
concept constexpr_value = std::same_as<decltype(value), value_type>;

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

template <class T, class... Ts>
extern std::bool_constant<(... && std::same_as<T, Ts>)> all_same;

} // namespace impl

template <class... Ts>
concept all_same = decltype(impl::all_same<Ts...>)::value;

namespace impl {

template <class T, class... Ts>
extern std::type_identity<T> front;

} // namespace impl

template <class... Ts>
using front = typename decltype(impl::front<Ts...>)::type;

} // namespace k3::tok3n::detail
