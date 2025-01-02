// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <concepts>
#include <functional>
#include <tuple>
#include <type_traits>

namespace k3::tok3n::detail {

namespace impl {

template <class F, class Tup, std::size_t... Is>
constexpr auto apply_invoke(F&& f, Tup&& tup, std::index_sequence<Is...>)
noexcept(noexcept(std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...)))
-> decltype(std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...))
{
    return std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...);
}

} // namespace impl

template <class F, class Tup>
requires requires { std::tuple_size<std::decay_t<Tup>>{}; }
constexpr auto apply_invoke(F&& f, Tup&& tup)
noexcept(noexcept(impl::apply_invoke(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<std::decay_t<Tup>>>{})))
-> decltype(impl::apply_invoke(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<std::decay_t<Tup>>>{}))
{
    return impl::apply_invoke(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<std::decay_t<Tup>>>{});
}

} // namespace k3::tok3n::detail
