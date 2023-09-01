#pragma once
#include <type_traits>

namespace k3::tok3n::detail {

template <auto F, class... Ts>
using invoke_type = decltype(F(std::declval<Ts>()...));

} // namespace k3::tok3n::detail
