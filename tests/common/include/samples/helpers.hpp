// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include "samples.hpp"

template <class T = ::value_type, class... Ts>
requires (... and std::convertible_to<T, Ts>)
consteval auto e(Ts... ts)
{
    return std::array<T, sizeof...(Ts)>{ ts... };
}

template <class T, k3::tok3n::detail::character U, std::size_t N>
requires std::convertible_to<T, U>
consteval auto e(const U(&us)[N])
{
    if constexpr (N - 1 == 0)
        return std::array<T, 0>{};
    else
    {
        std::array<T, N - 1> arr;
        for (std::size_t i = 0; i != N - 1; ++i)
            arr[i] = us[i];
        return arr;
    }
}
