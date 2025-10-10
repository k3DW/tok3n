// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework/Assert.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <k3/tok3n/detail/result.hpp>
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
    SIMPLE_EXPECT((detail::optional_like<detail::result<int, char>>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<int, char>>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<int, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<int, char>&>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<int, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<int, char>&&>));

    SIMPLE_EXPECT((detail::optional_like<detail::result<double, char>>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<double, char>>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<double, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<double, char>&>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<double, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<double, char>&&>));

    SIMPLE_EXPECT((detail::optional_like<detail::result<char, char>>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<char, char>>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<char, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<char, char>&>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<char, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<char, char>&&>));

    SIMPLE_EXPECT((detail::optional_like<detail::result<wchar_t, char>>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<wchar_t, char>>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<wchar_t, char>&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<wchar_t, char>&>));
    SIMPLE_EXPECT((detail::optional_like<detail::result<wchar_t, char>&&>));
    SIMPLE_EXPECT((detail::optional_like<const detail::result<wchar_t, char>&&>));
}
