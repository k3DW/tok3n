#pragma once
#include <type_traits>

namespace k3::tok3n {

template <std::size_t N>
using Index = std::integral_constant<std::size_t, N>;

} // namespace k3::tok3n
