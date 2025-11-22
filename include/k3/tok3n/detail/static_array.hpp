// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_STATIC_ARRAY_HPP
#define K3_TOK3N_DETAIL_STATIC_ARRAY_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <span>
#include <string_view>
#include <k3/tok3n/detail/type_traits.hpp>

namespace k3::tok3n::detail {

template <class T, std::size_t N>
struct static_array
{
    std::array<T, N> data = {};

    constexpr static_array() = default;

    template <class... Ts>
    requires (sizeof...(Ts) == N - 1) and (... and std::convertible_to<Ts, T>)
    constexpr static_array(T t, Ts... ts)
        : data{{t, static_cast<Ts>(ts)...}}
    {}

    constexpr static_array(const T(&input)[N + 1]) noexcept requires character<T>
    {
        for (std::size_t i = 0; i != N; ++i)
            data[i] = input[i];
    }

    constexpr static_array(T c) noexcept requires (N == 1)
    {
        data[0] = c;
    }

    constexpr std::span<const T> span() const
    {
        return { data.data(), N };
    }

    constexpr std::basic_string_view<T> view() const requires character<T>
    {
        return { data.data(), N };
    }

    template <class U>
    constexpr bool contains(U&& u) const
    {
        for (const auto& element : data)
            if (element == u)
                return true;
        return false;
    }

    constexpr auto begin() const { return data.begin(); }
    constexpr auto begin()       { return data.begin(); }
    constexpr auto end()   const { return data.end(); }
    constexpr auto end()         { return data.end(); }

    constexpr const T& operator[](std::size_t i) const { return data[i]; }
    constexpr       T& operator[](std::size_t i)       { return data[i]; }

    consteval std::size_t size() const noexcept { return N; }

    using value_type = T;

    template <std::size_t M>
    static constexpr auto create_empty_with_size() { return static_array<T, M>{}; }
};

template <class T, class... Ts>
requires (... and std::convertible_to<Ts, T>)
static_array(T, Ts...) -> static_array<T, sizeof...(Ts) + 1>;

template <character T, std::size_t N>
static_array(const T(&)[N]) -> static_array<T, N - 1>;

template <class T>
static_array(T) -> static_array<T, 1>;



template <class T1, std::size_t N1, class T2, std::size_t N2>
extern std::is_same<T1, T2> like_static_arrays(const static_array<T1, N1>&, const static_array<T2, N2>&);



template <class T>
constexpr bool is_sorted_and_uniqued(std::span<const T> span)
{
    const auto N = span.size();
    if (N == 0)
        return true;

    for (std::size_t i = 0; i != N - 1; ++i)
        if (span[i + 1] <= span[i])
            return false;
    return true;
}

template <static_array str> // Must be a template parameter because the return type depends on it
consteval auto sort_and_unique()
{
    if constexpr (is_sorted_and_uniqued(str.span()))
        return str;

    else
    {
        constexpr auto sorted = []
        {
            auto copy = str;
            std::ranges::sort(copy);
            return copy;
        }();

        constexpr auto pair = [copy = sorted]() mutable
        {
            auto subrange = std::ranges::unique(copy);
            auto new_size = subrange.begin() - copy.begin();
            return std::make_pair(std::move(copy), new_size);
        }();

        auto out = str.template create_empty_with_size<pair.second>();
        std::ranges::copy_n(pair.first.begin(), pair.second, out.begin());
        return out;
    }
}



template <class T, std::size_t M, std::size_t N>
constexpr bool operator==(const static_array<T, M>& lhs, const static_array<T, N>& rhs)
{
    if constexpr (M != N)
        return false;
    else
        return lhs.data == rhs.data;
}

template <class T, std::size_t M, std::size_t N>
constexpr static_array<T, M + N> operator+(const static_array<T, M>& lhs, const static_array<T, N>& rhs)
{
    static_array<T, M + N> str;
    for (std::size_t i = 0; i != M; ++i)
        str[i] = lhs[i];
    for (std::size_t i = 0; i != N; ++i)
        str[i + M] = rhs[i];
    return str;
}

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_STATIC_ARRAY_HPP
