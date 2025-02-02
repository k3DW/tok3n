// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_SUBSTITUTION_HPP
#define K3_TOK3N_DETAIL_SUBSTITUTION_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/static_array.hpp>

namespace k3::tok3n::detail {

template <static_array Name, modifier Mod>
struct substitution_info
{
    static constexpr auto name = Name;
    static constexpr auto mod = Mod{};
};

template <class T>
inline constexpr bool is_substitution_v = false;
template <class T>
inline constexpr bool is_substitution_v<const T> = is_substitution_v<T>;
template <class T>
inline constexpr bool is_substitution_v<T&> = is_substitution_v<T>;
template <class T>
inline constexpr bool is_substitution_v<T&&> = is_substitution_v<T>;
template <static_array Name, modifier Mod>
inline constexpr bool is_substitution_v<substitution_info<Name, Mod>> = true;

template <class T>
concept substitution = is_substitution_v<T>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_SUBSTITUTION_HPP
