#pragma once
#include <concepts>

namespace k3::tok3n::detail {

template <class T, class... Ts>
concept all_same = (... && std::same_as<T, Ts>);

} // namespace k3::tok3n::detail
