#pragma once
#include <type_traits>

namespace k3::tok3n {

template <auto val>
using Const = std::integral_constant<decltype(val), val>;

template <std::size_t N>
using Index = Const<N>;

} // namespace k3::tok3n
