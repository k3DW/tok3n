// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_APPLY_HPP
#define K3_TOK3N_DETAIL_APPLY_HPP

#include <k3/tok3n/detail/type_traits.hpp>
#include <concepts>
#include <functional>
#include <tuple>
#include <type_traits>

namespace k3::tok3n::detail {

namespace impl {

template <class F, class Tup, std::size_t... Is>
constexpr auto apply_invoke(F&& f, Tup&& tup, std::index_sequence<Is...>)
noexcept(noexcept(std::invoke(std::forward<F>(f), adl_get<Is>(std::forward<Tup>(tup))...)))
-> decltype(std::invoke(std::forward<F>(f), adl_get<Is>(std::forward<Tup>(tup))...))
{
    return std::invoke(std::forward<F>(f), adl_get<Is>(std::forward<Tup>(tup))...);
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

#endif // K3_TOK3N_DETAIL_APPLY_HPP
