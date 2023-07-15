#pragma once
#include <type_traits>

namespace k3::tok3n {

template <std::size_t N>
using Index = std::integral_constant<std::size_t, N>;

template <auto val>
using Const = std::integral_constant<decltype(val), val>;

using True  = std::true_type;
using False = std::false_type;

} // namespace k3::tok3n
