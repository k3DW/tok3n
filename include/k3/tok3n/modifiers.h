#pragma once

#include <k3/tok3n/detail/modifiers/apply_into.h>
#include <k3/tok3n/detail/modifiers/apply.h>
#include <k3/tok3n/detail/modifiers/complete.h>
#include <k3/tok3n/detail/modifiers/constant.h>
#include <k3/tok3n/detail/modifiers/defaulted.h>
#include <k3/tok3n/detail/modifiers/delimit.h>
#include <k3/tok3n/detail/modifiers/delimit_keep.h>
#include <k3/tok3n/detail/modifiers/exactly.h>
#include <k3/tok3n/detail/modifiers/filter.h>
#include <k3/tok3n/detail/modifiers/ignore.h>
#include <k3/tok3n/detail/modifiers/into.h>
#include <k3/tok3n/detail/modifiers/join.h>
#include <k3/tok3n/detail/modifiers/map.h>
#include <k3/tok3n/detail/modifiers/multi.h>
#include <k3/tok3n/detail/modifiers/name.h>
#include <k3/tok3n/detail/modifiers/sub.h>

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