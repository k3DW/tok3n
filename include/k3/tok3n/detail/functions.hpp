// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_FUNCTIONS_HPP
#define K3_TOK3N_DETAIL_FUNCTIONS_HPP

#include <k3/tok3n/detail/apply.hpp>
#include <k3/tok3n/detail/type_traits.hpp>

namespace k3::tok3n::detail {

template <auto function>
inline constexpr auto apply_function = []<class Tup>(Tup&& tup) { return apply_invoke(function, std::forward<Tup>(tup)); };

template <auto value>
inline constexpr auto constant_function = [](auto&&...) { return value; };

template <class T>
inline constexpr auto construct_function = []<class... Args>(Args&&... args) { return T(std::forward<Args>(args)...); };

template <class T>
requires std::is_default_constructible_v<T>
inline constexpr auto default_construct_function = [](auto&&...) { return T{}; };

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_FUNCTIONS_HPP
