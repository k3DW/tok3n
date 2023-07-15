#pragma once
#include <concepts>
#include <type_traits>

namespace k3::tok3n::detail {

template <class T>
constexpr bool is_integral_constant_v = false;

template <class T, T val>
constexpr bool is_integral_constant_v<std::integral_constant<T, val>> = true;

template <class T, class value_type = void>
concept is_integral_constant = is_integral_constant_v<T> and
	(std::same_as<value_type, void> or std::same_as<value_type, typename T::value_type>);

} // namespace k3::tok3n::detail
