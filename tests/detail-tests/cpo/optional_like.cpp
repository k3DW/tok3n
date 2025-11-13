// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <k3/tok3n/result.hpp>
#include <optional>

FIXTURE("optional_like");

using namespace k3::tok3n;

TEST("optional_like", "std::optional")
{
    SIMPLE_EXPECT((detail::optional_like<std::optional<int>>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<int>>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<int>&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<int>&>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<int>&&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<int>&&>));

    SIMPLE_EXPECT((detail::optional_like<std::optional<double>>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<double>>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<double>&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<double>&>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<double>&&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<double>&&>));

    SIMPLE_EXPECT((detail::optional_like<std::optional<char>>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<char>>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<char>&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<char>&>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<char>&&>));

    SIMPLE_EXPECT((detail::optional_like<std::optional<wchar_t>>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<wchar_t>>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<wchar_t>&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<wchar_t>&>));
    SIMPLE_EXPECT((detail::optional_like<std::optional<wchar_t>&&>));
    SIMPLE_EXPECT((detail::optional_like<const std::optional<wchar_t>&&>));
}

TEST("optional_like", "tok3n result")
{
    SIMPLE_EXPECT((detail::optional_like<result<int, char>>));
    SIMPLE_EXPECT((detail::optional_like<const result<int, char>>));
    SIMPLE_EXPECT((detail::optional_like<result<int, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const result<int, char>&>));
    SIMPLE_EXPECT((detail::optional_like<result<int, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const result<int, char>&&>));

    SIMPLE_EXPECT((detail::optional_like<result<double, char>>));
    SIMPLE_EXPECT((detail::optional_like<const result<double, char>>));
    SIMPLE_EXPECT((detail::optional_like<result<double, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const result<double, char>&>));
    SIMPLE_EXPECT((detail::optional_like<result<double, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const result<double, char>&&>));

    SIMPLE_EXPECT((detail::optional_like<result<char, char>>));
    SIMPLE_EXPECT((detail::optional_like<const result<char, char>>));
    SIMPLE_EXPECT((detail::optional_like<result<char, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const result<char, char>&>));
    SIMPLE_EXPECT((detail::optional_like<result<char, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const result<char, char>&&>));

    SIMPLE_EXPECT((detail::optional_like<result<wchar_t, char>>));
    SIMPLE_EXPECT((detail::optional_like<const result<wchar_t, char>>));
    SIMPLE_EXPECT((detail::optional_like<result<wchar_t, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const result<wchar_t, char>&>));
    SIMPLE_EXPECT((detail::optional_like<result<wchar_t, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const result<wchar_t, char>&&>));
}
