#pragma once
#include <k3/tok3n/meta/invoke_type.h>
#include <concepts>

namespace k3::tok3n::meta {

template <class T, class... Ts>
concept all_same = (... && std::same_as<T, Ts>);

} // namespace k3::tok3n::meta
