#pragma once
#include <type_traits>

namespace k3::tok3n::detail {

template <class T, class... Ts>
extern std::type_identity<T> head_impl;

template <class... Ts>
using head = typename decltype(head_impl<Ts...>)::type;

} // namespace k3::tok3n::detail
