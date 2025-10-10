// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_FUNCTIONS_HPP
#define K3_TOK3N_TESTS_SAMPLES_FUNCTIONS_HPP

#include "samples.hpp"

constexpr std::size_t func1(std::vector<k3::tok3n::detail::output_span<::value_type>>&& vec)
{
    return vec.size();
}

inline constexpr auto func2 = []<class T>(const std::optional<k3::tok3n::detail::output_span<T>>& opt) -> std::vector<T>
{
    if (not opt.has_value())
        return {};
    else
    {
        auto& sv = *opt;
        return { sv.begin(), sv.end() };
    }
};

constexpr struct func3_t
{
    constexpr bool operator()(std::tuple<k3::tok3n::detail::output_span<char>, std::vector<k3::tok3n::detail::output_span<char>>>&& tup) const
    {
        auto&& [sv, vec] = std::move(tup);
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(std::tuple<k3::tok3n::detail::output_span<wchar_t>, std::vector<k3::tok3n::detail::output_span<wchar_t>>>&& tup) const
    {
        auto&& [sv, vec] = std::move(tup);
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(std::tuple<k3::tok3n::detail::output_span<int>, std::vector<k3::tok3n::detail::output_span<int>>>&& tup) const
    {
        auto&& [sv, vec] = std::move(tup);
        return vec.size() % 2 == 0;
    }
} func3;

constexpr struct func3_apply_t
{
    constexpr bool operator()(k3::tok3n::detail::output_span<char>, std::vector<k3::tok3n::detail::output_span<char>>&& vec) const
    {
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(k3::tok3n::detail::output_span<wchar_t>, std::vector<k3::tok3n::detail::output_span<wchar_t>>&& vec) const
    {
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(k3::tok3n::detail::output_span<int>, std::vector<k3::tok3n::detail::output_span<int>>&& vec) const
    {
        return vec.size() % 2 == 0;
    }
} func3_apply;

struct func4
{
    constexpr func4(int multiply_by)
        : multiply_by(multiply_by) {}

    int multiply_by;

    constexpr std::size_t operator()(const std::tuple<std::vector<k3::tok3n::detail::output_span<char>>, std::optional<k3::tok3n::detail::output_span<char>>>& tup) const
    {
        const auto& [vec, opt] = tup;
        return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
    }

    constexpr std::size_t operator()(const std::tuple<std::vector<k3::tok3n::detail::output_span<wchar_t>>, std::optional<k3::tok3n::detail::output_span<wchar_t>>>& tup) const
    {
        const auto& [vec, opt] = tup;
        return multiply_by * vec.size() * (not opt ? 1 : *opt == L"abc" ? 2 : 3);
    }

    constexpr std::size_t operator()(const std::tuple<std::vector<k3::tok3n::detail::output_span<int>>, std::optional<k3::tok3n::detail::output_span<int>>>& tup) const
    {
        const auto& [vec, opt] = tup;
        return multiply_by * vec.size() * (not opt ? 1 : *opt == e<int>("abc") ? 2 : 3);
    }
};

struct func4_apply
{
    constexpr func4_apply(int multiply_by)
        : multiply_by(multiply_by) {}

    int multiply_by;

    constexpr std::size_t operator()(const std::vector<k3::tok3n::detail::output_span<char>>& vec, const std::optional<k3::tok3n::detail::output_span<char>>& opt) const
    {
        return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
    }

    constexpr std::size_t operator()(const std::vector<k3::tok3n::detail::output_span<wchar_t>>& vec, const std::optional<k3::tok3n::detail::output_span<wchar_t>>& opt) const
    {
        return multiply_by * vec.size() * (not opt ? 1 : *opt == L"abc" ? 2 : 3);
    }

    constexpr std::size_t operator()(const std::vector<k3::tok3n::detail::output_span<int>>& vec, const std::optional<k3::tok3n::detail::output_span<int>>& opt) const
    {
        return multiply_by * vec.size() * (not opt ? 1 : *opt == e<int>("abc") ? 2 : 3);
    }
};

constexpr bool filter_func1(const std::vector<k3::tok3n::detail::output_span<::value_type>>& vec)
{
    return vec.size() % 2 == 0;
}

inline constexpr auto filter_func2 = []<class T>(const std::optional<k3::tok3n::detail::output_span<T>>& opt)
{
    return opt.has_value();
};

constexpr struct filter_func3_t
{
    constexpr bool operator()(const std::tuple<k3::tok3n::detail::output_span<char>, std::vector<k3::tok3n::detail::output_span<char>>>& tup) const
    {
        auto&& [sv, vec] = std::move(tup);
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(const std::tuple<k3::tok3n::detail::output_span<wchar_t>, std::vector<k3::tok3n::detail::output_span<wchar_t>>>& tup) const
    {
        auto&& [sv, vec] = std::move(tup);
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(const std::tuple<k3::tok3n::detail::output_span<int>, std::vector<k3::tok3n::detail::output_span<int>>>& tup) const
    {
        auto&& [sv, vec] = std::move(tup);
        return vec.size() % 2 == 0;
    }
} filter_func3;

constexpr struct filter_func3_apply_t
{
    constexpr bool operator()(const k3::tok3n::detail::output_span<char>&, const std::vector<k3::tok3n::detail::output_span<char>>& vec) const
    {
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(const k3::tok3n::detail::output_span<wchar_t>&, const std::vector<k3::tok3n::detail::output_span<wchar_t>>& vec) const
    {
        return vec.size() % 2 == 0;
    }

    constexpr bool operator()(const k3::tok3n::detail::output_span<int>&, const std::vector<k3::tok3n::detail::output_span<int>>& vec) const
    {
        return vec.size() % 2 == 0;
    }
} filter_func3_apply;

inline constexpr auto sink_func = [](auto&&...) {};

inline constexpr auto true_filter = [](auto&&...) { return true; };

#endif // K3_TOK3N_TESTS_SAMPLES_FUNCTIONS_HPP
