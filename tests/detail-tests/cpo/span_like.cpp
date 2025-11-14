// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <k3/tok3n/detail/cpo.hpp>
#include <k3/tok3n/span.hpp>
#include <span>
#include <string_view>

FIXTURE("span_like");

using namespace k3::tok3n;

TEST("span_like", "std::span")
{
    EXPECT_COMPILE_TIME((detail::span_like<std::span<double>>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<double>>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<double>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<double>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<std::span<const double>>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<const double>>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<const double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<const double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<const double>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<const double>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<std::span<int>>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<int>>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<int>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<int>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<std::span<const int>>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<const int>>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<const int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<const int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<std::span<const int>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::span<const int>&&>));
}

TEST("span_like", "std::string_view")
{
    EXPECT_COMPILE_TIME((detail::span_like<std::string_view>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::string_view>));
    EXPECT_COMPILE_TIME((detail::span_like<std::string_view&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::string_view&>));
    EXPECT_COMPILE_TIME((detail::span_like<std::string_view&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::string_view&&>));

    EXPECT_COMPILE_TIME((detail::span_like<std::wstring_view>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::wstring_view>));
    EXPECT_COMPILE_TIME((detail::span_like<std::wstring_view&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::wstring_view&>));
    EXPECT_COMPILE_TIME((detail::span_like<std::wstring_view&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const std::wstring_view&&>));
}

TEST("span_like", "tok3n input_span")
{
    EXPECT_COMPILE_TIME((detail::span_like<input_span<int>>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<int>>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<int>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<int>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<input_span<double>>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<double>>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<double>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<double>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<input_span<char>>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<char>>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<char>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<char>&>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<char>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<char>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<input_span<wchar_t>>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<wchar_t>>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<wchar_t>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<wchar_t>&>));
    EXPECT_COMPILE_TIME((detail::span_like<input_span<wchar_t>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const input_span<wchar_t>&&>));
}

TEST("span_like", "tok3n output_span")
{
    EXPECT_COMPILE_TIME((detail::span_like<output_span<int>>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<int>>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<int>&>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<int>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<int>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<output_span<double>>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<double>>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<double>&>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<double>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<double>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<output_span<char>>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<char>>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<char>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<char>&>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<char>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<char>&&>));

    EXPECT_COMPILE_TIME((detail::span_like<output_span<wchar_t>>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<wchar_t>>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<wchar_t>&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<wchar_t>&>));
    EXPECT_COMPILE_TIME((detail::span_like<output_span<wchar_t>&&>));
    EXPECT_COMPILE_TIME((detail::span_like<const output_span<wchar_t>&&>));
}
