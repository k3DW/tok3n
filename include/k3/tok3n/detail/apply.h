#pragma once
#include <concepts>
#include <tuple>
#include <type_traits>

namespace k3::tok3n::detail {

namespace impl {

template <class F, class Tup, std::size_t... Is>
requires requires (F&& f, Tup&& tup)
{
    std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...);
}
constexpr decltype(auto) apply_invoke(F&& f, Tup&& tup, std::index_sequence<Is...>)
noexcept(noexcept(std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...)))
{
    return std::invoke(std::forward<F>(f), std::get<Is>(std::forward<Tup>(tup))...);
}

} // namespace impl

template <class F, class Tup>
requires requires (F&& f, Tup&& tup)
{
    impl::apply_invoke(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<Tup>>{});
}
constexpr decltype(auto) apply_invoke(F&& f, Tup&& tup)
noexcept(noexcept(impl::apply_invoke(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<Tup>>{})))
{
    return impl::apply_invoke(std::forward<F>(f), std::forward<Tup>(tup), std::make_index_sequence<std::tuple_size_v<Tup>>{});
}

} // namespace k3::tok3n::detail
