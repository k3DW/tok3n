// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <k3/tok3n/result.hpp>
#include <optional>

namespace k3::tok3n::tests {
namespace {

FIXTURE("optional_like");

TEST("optional_like", "std::optional")
{
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<int>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<int>>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<int>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<int>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<int>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<int>&&>));

    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<double>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<double>>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<double>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<double>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<double>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<double>&&>));

    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<char>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<char>&&>));

    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<wchar_t>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<wchar_t>>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<wchar_t>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<wchar_t>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<std::optional<wchar_t>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const std::optional<wchar_t>&&>));
}

TEST("optional_like", "tok3n result")
{
    EXPECT_COMPILE_TIME((detail::optional_like<result<int, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<int, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<int, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<int, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<int, char>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<int, char>&&>));

    EXPECT_COMPILE_TIME((detail::optional_like<result<double, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<double, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<double, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<double, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<double, char>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<double, char>&&>));

    EXPECT_COMPILE_TIME((detail::optional_like<result<char, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<char, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<char, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<char, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<char, char>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<char, char>&&>));

    EXPECT_COMPILE_TIME((detail::optional_like<result<wchar_t, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<wchar_t, char>>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<wchar_t, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<wchar_t, char>&>));
    EXPECT_COMPILE_TIME((detail::optional_like<result<wchar_t, char>&&>));
    EXPECT_COMPILE_TIME((detail::optional_like<const result<wchar_t, char>&&>));
}

} // namespace
} // namespace k3::tok3n::tests
