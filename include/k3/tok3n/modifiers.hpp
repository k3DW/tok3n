// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_MODIFIERS_HPP
#define K3_TOK3N_MODIFIERS_HPP

#include <k3/tok3n/detail/modifiers/apply_filter.hpp>
#include <k3/tok3n/detail/modifiers/apply_into.hpp>
#include <k3/tok3n/detail/modifiers/apply.hpp>
#include <k3/tok3n/detail/modifiers/complete.hpp>
#include <k3/tok3n/detail/modifiers/constant.hpp>
#include <k3/tok3n/detail/modifiers/defaulted.hpp>
#include <k3/tok3n/detail/modifiers/delimit.hpp>
#include <k3/tok3n/detail/modifiers/delimit_keep.hpp>
#include <k3/tok3n/detail/modifiers/exactly.hpp>
#include <k3/tok3n/detail/modifiers/filter.hpp>
#include <k3/tok3n/detail/modifiers/ignore.hpp>
#include <k3/tok3n/detail/modifiers/into.hpp>
#include <k3/tok3n/detail/modifiers/join.hpp>
#include <k3/tok3n/detail/modifiers/map.hpp>
#include <k3/tok3n/detail/modifiers/multi.hpp>
#include <k3/tok3n/detail/modifiers/name.hpp>
#include <k3/tok3n/detail/modifiers/sub.hpp>

namespace k3::tok3n {

template <auto function>
inline constexpr auto apply_filter = detail::apply_filter_modifier<function>{};

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

template <auto function>
inline constexpr auto filter = detail::filter_modifier<function>{};

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

#endif // K3_TOK3N_MODIFIERS_HPP
