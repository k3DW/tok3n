#pragma once
#include <k3/tok3n/namespace.h>
#include <tuple>

TOK3N_BEGIN_NAMESPACE()

template <class T>
concept has_tuple_size = requires { std::tuple_size<T>{}; } && (std::tuple_size_v<T> > 0);

TOK3N_END_NAMESPACE()
