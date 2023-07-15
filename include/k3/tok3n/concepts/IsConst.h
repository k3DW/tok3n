#pragma once
#include <concepts>

namespace k3::tok3n {

template <class T, class value_type = void>
concept IsConst =
	requires { typename T::value_type; } and
	(std::same_as<value_type, void> or std::same_as<value_type, typename T::value_type>) and
	requires {
		{ T{}.operator typename T::value_type() } -> std::same_as<typename T::value_type>;
		{ T{}() } -> std::same_as<typename T::value_type>;
		{ T::value } -> std::same_as<const typename T::value_type&>;
	};

} // namespace k3::tok3n
