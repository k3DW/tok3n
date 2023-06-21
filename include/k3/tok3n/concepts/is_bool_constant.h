#pragma once
#include <k3/tok3n/namespace.h>
#include <concepts>
#include <type_traits>

TOK3N_BEGIN_NAMESPACE()

template <class T>
concept is_bool_constant = std::same_as<T, std::true_type> or std::same_as<T, std::false_type>;

TOK3N_END_NAMESPACE()
