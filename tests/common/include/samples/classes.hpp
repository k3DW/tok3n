// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_SAMPLES_CLASSES_HPP
#define K3_TOK3N_TESTS_SAMPLES_CLASSES_HPP

#include "samples.hpp"

class Class1
{
public:
    constexpr Class1() = default;

    explicit constexpr Class1(int value) : value(value) {}

    template <class T>
    explicit constexpr Class1(k3::tok3n::detail::output_span<T> sv)
    {
        if (sv.size() == 1)
        {
            switch (sv.front())
            {
            break; case ' ': value = 0;
            break; case '.': value = 1;
            break; default:  value = 2;
            }
        }
        else
            value = 3;
    }

    friend constexpr bool operator==(const Class1&, const Class1&) = default;

private:
    int value;
};

class Class2
{
public:
    constexpr Class2() = default;

    explicit constexpr Class2(k3::tok3n::detail::output_span<char> sv1, k3::tok3n::detail::output_span<char> sv2)
        : sv1(sv1), sv2(sv2) {}

    template <std::size_t M, std::size_t N>
    explicit constexpr Class2(const char(&sv1)[M], const char(&sv2)[N])
        : sv1(sv1), sv2(sv2) {}

    explicit constexpr Class2(const std::tuple<k3::tok3n::detail::output_span<char>, k3::tok3n::detail::output_span<char>>& tup)
        : sv1(std::get<0>(tup)), sv2(std::get<1>(tup)) {}

    explicit constexpr Class2(k3::tok3n::detail::output_span<wchar_t> sv1, k3::tok3n::detail::output_span<wchar_t> sv2)
        : sv1(sv1), sv2(sv2) {}

    template <std::size_t M, std::size_t N>
    explicit constexpr Class2(const wchar_t(&sv1)[M], const wchar_t(&sv2)[N])
        : sv1(sv1), sv2(sv2) {}

    explicit constexpr Class2(const std::tuple<k3::tok3n::detail::output_span<wchar_t>, k3::tok3n::detail::output_span<wchar_t>>& tup)
        : sv1(std::get<0>(tup)), sv2(std::get<1>(tup)) {}

    explicit constexpr Class2(k3::tok3n::detail::output_span<int> sv1, k3::tok3n::detail::output_span<int> sv2)
        : sv1(sv1), sv2(sv2) {}

    template <std::size_t M, std::size_t N>
    explicit constexpr Class2(const std::array<int, M>& sv1, const std::array<int, N>& sv2)
        : sv1(sv1), sv2(sv2) {}

    explicit constexpr Class2(const std::tuple<k3::tok3n::detail::output_span<int>, k3::tok3n::detail::output_span<int>>& tup)
        : sv1(std::get<0>(tup)), sv2(std::get<1>(tup)) {}

    friend constexpr bool operator==(const Class2&, const Class2&) = default;

private:
    using Variant = std::variant<k3::tok3n::detail::output_span<char>, k3::tok3n::detail::output_span<wchar_t>, k3::tok3n::detail::output_span<int>>;
    Variant sv1;
    Variant sv2;

public:
    explicit constexpr Class2(Variant sv1, Variant sv2)
        : sv1(sv1), sv2(sv2) {}
};

class Class3
{
public:
    friend constexpr bool operator==(const Class3&, const Class3&) = default;
};

class Class4
{
public:
    constexpr Class4() = default;

    explicit constexpr Class4(const std::tuple<k3::tok3n::detail::output_span<char>, k3::tok3n::detail::output_span<char>>& tup)
        : sv1(std::get<0>(tup)), sv2(std::get<1>(tup)) {}

    explicit constexpr Class4(const std::tuple<k3::tok3n::detail::output_span<wchar_t>, k3::tok3n::detail::output_span<wchar_t>>& tup)
        : sv1(std::get<0>(tup)), sv2(std::get<1>(tup)) {}

    explicit constexpr Class4(const std::tuple<k3::tok3n::detail::output_span<int>, k3::tok3n::detail::output_span<int>>& tup)
        : sv1(std::get<0>(tup)), sv2(std::get<1>(tup)) {}

    explicit constexpr operator Class2() const { return Class2{ sv1, sv2 }; }

private:
    using Variant = std::variant<k3::tok3n::detail::output_span<char>, k3::tok3n::detail::output_span<wchar_t>, k3::tok3n::detail::output_span<int>>;
    Variant sv1;
    Variant sv2;
};

class Class5
{
public:
    constexpr Class5() = default;

    explicit constexpr Class5(k3::tok3n::detail::output_span<char> sv1, k3::tok3n::detail::output_span<char> sv2)
        : sv1(sv1), sv2(sv2) {}

    explicit constexpr Class5(k3::tok3n::detail::output_span<wchar_t> sv1, k3::tok3n::detail::output_span<wchar_t> sv2)
        : sv1(sv1), sv2(sv2) {}

    explicit constexpr Class5(k3::tok3n::detail::output_span<int> sv1, k3::tok3n::detail::output_span<int> sv2)
        : sv1(sv1), sv2(sv2) {}

    friend constexpr bool operator==(const Class5&, const Class5&) = default;

private:
    using Variant = std::variant<k3::tok3n::detail::output_span<char>, k3::tok3n::detail::output_span<wchar_t>, k3::tok3n::detail::output_span<int>>;
    Variant sv1;
    Variant sv2;
};

struct Sink
{
    constexpr Sink(auto&&...) {};
};

#endif // K3_TOK3N_TESTS_SAMPLES_CLASSES_HPP
