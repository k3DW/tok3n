#pragma once
#include <k3/tok3n/detail/has_tuple_size.h>
#include <concepts>
#include <type_traits>

namespace k3::tok3n::detail {

template <class F, class Tup, std::size_t... Is>
requires requires (F&& f, Tup&& tup)
{
    std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...);
}
constexpr decltype(auto) apply_impl(F&& f, Tup&& tup, std::index_sequence<Is...>)
{
    return std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...);
}

template <class F, class Tup>
requires requires (F&& f, Tup&& tup)
{
    apply_impl(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<Tup>>{});
}
constexpr decltype(auto) apply(F&& f, Tup&& tup)
{
    return apply_impl(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<Tup>>{});
}

} // namespace k3::tok3n::detail
