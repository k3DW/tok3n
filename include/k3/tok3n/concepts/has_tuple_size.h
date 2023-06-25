#pragma once
#include <k3/tok3n/namespace.h>
#include <tuple>

namespace k3::tok3n {

template <class T>
concept has_tuple_size = requires { std::tuple_size<T>{}; } && (std::tuple_size_v<T> > 0);

} // namespace k3::tok3n
