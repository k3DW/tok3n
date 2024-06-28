#pragma once
#include <concepts>

namespace k3::tok3n::detail {

template <class T, class... Ts>
consteval bool all_same_impl()
{
    return (... && std::same_as<T, Ts>);
}

template <class... Ts>
concept all_same = all_same_impl<Ts...>();

} // namespace k3::tok3n::detail
