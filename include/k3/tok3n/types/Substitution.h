#pragma once
#include <k3/tok3n/concepts/Modifier.h>
#include <k3/tok3n/types/StaticArray.h>

namespace k3::tok3n {

template <StaticArray Name, Modifier Mod>
struct Substitution
{
    static constexpr auto name = Name;
    static constexpr auto mod = Mod{};
};

namespace detail {

template <class T>
inline constexpr bool is_substitution_v = false;
template <class T>
inline constexpr bool is_substitution_v<const T> = is_substitution_v<T>;
template <class T>
inline constexpr bool is_substitution_v<T&> = is_substitution_v<T>;
template <class T>
inline constexpr bool is_substitution_v<T&&> = is_substitution_v<T>;
template <StaticArray Name, Modifier Mod>
inline constexpr bool is_substitution_v<Substitution<Name, Mod>> = true;

} // namespace detail

template <class T>
concept IsSubstitution = detail::is_substitution_v<T>;

} // namespace k3::tok3n
