#pragma once
#include <concepts>
#include <type_traits>

namespace k3::tok3n {

template <class T>
concept is_bool_constant = std::same_as<T, std::true_type> or std::same_as<T, std::false_type>;

} // namespace k3::tok3n
