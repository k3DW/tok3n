// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework/Assert.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <array>
#include <tuple>
#include <utility>

FIXTURE("tuple_like");

using namespace k3::tok3n;

TEST("tuple_like", "std::tuple")
{
    SIMPLE_EXPECT((detail::tuple_like<std::tuple<int, double, char>>));
    SIMPLE_EXPECT((detail::tuple_like<const std::tuple<int, double, char>>));
    SIMPLE_EXPECT((detail::tuple_like<std::tuple<int, double, char>&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::tuple<int, double, char>&>));
    SIMPLE_EXPECT((detail::tuple_like<std::tuple<int, double, char>&&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::tuple<int, double, char>&&>));
}

TEST("tuple_like", "std::array")
{
    SIMPLE_EXPECT((detail::tuple_like<std::array<int, 3>>));
    SIMPLE_EXPECT((detail::tuple_like<const std::array<int, 3>>));
    SIMPLE_EXPECT((detail::tuple_like<std::array<int, 3>&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::array<int, 3>&>));
    SIMPLE_EXPECT((detail::tuple_like<std::array<int, 3>&&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::array<int, 3>&&>));

    SIMPLE_EXPECT((detail::tuple_like<std::array<double, 5>>));
    SIMPLE_EXPECT((detail::tuple_like<const std::array<double, 5>>));
    SIMPLE_EXPECT((detail::tuple_like<std::array<double, 5>&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::array<double, 5>&>));
    SIMPLE_EXPECT((detail::tuple_like<std::array<double, 5>&&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::array<double, 5>&&>));
}

TEST("tuple_like", "std::pair")
{
    SIMPLE_EXPECT((detail::tuple_like<std::pair<int, double>>));
    SIMPLE_EXPECT((detail::tuple_like<const std::pair<int, double>>));
    SIMPLE_EXPECT((detail::tuple_like<std::pair<int, double>&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::pair<int, double>&>));
    SIMPLE_EXPECT((detail::tuple_like<std::pair<int, double>&&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::pair<int, double>&&>));

    SIMPLE_EXPECT((detail::tuple_like<std::pair<char, wchar_t>>));
    SIMPLE_EXPECT((detail::tuple_like<const std::pair<char, wchar_t>>));
    SIMPLE_EXPECT((detail::tuple_like<std::pair<char, wchar_t>&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::pair<char, wchar_t>&>));
    SIMPLE_EXPECT((detail::tuple_like<std::pair<char, wchar_t>&&>));
    SIMPLE_EXPECT((detail::tuple_like<const std::pair<char, wchar_t>&&>));
}
