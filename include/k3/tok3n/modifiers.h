#pragma once
#include <k3/tok3n/detail/modifiers.h>

namespace k3::tok3n {

template <class T>
inline constexpr auto apply_into = detail::apply_into_modifier<T>{};

template <auto function>
inline constexpr auto apply = detail::apply_modifier<function>{};

inline constexpr auto complete = detail::complete_modifier{};

template <auto value>
inline constexpr auto constant = detail::constant_modifier<value>{};

template <class T>
inline constexpr auto defaulted = detail::defaulted_modifier<T>{};

inline constexpr auto delimit_keep = detail::delimit_keep_modifier{};

inline constexpr auto delimit = detail::delimit_modifier{};

template <std::size_t N>
inline constexpr auto exactly = detail::exactly_modifier<N>{};

inline constexpr auto ignore = detail::ignore_modifier{};

template <class T>
inline constexpr auto into = detail::into_modifier<T>{};

inline constexpr auto join = detail::join_modifier{};

template <auto function>
inline constexpr auto map = detail::map_modifier<function>{};

template <detail::static_array s>
inline constexpr auto name = detail::name_modifier<s>{};

inline constexpr auto sub = detail::sub_modifier{};

} // namespace k3::tok3n