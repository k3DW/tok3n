#pragma once
#include <type_traits>

namespace k3::tok3n {

template <class T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

} // namespace k3::tok3n
