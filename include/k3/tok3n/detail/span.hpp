// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_SPAN_HPP
#define K3_TOK3N_DETAIL_SPAN_HPP

#include <ranges>
#include <span>
#include <string_view>
#include <k3/tok3n/detail/type_traits.hpp>

namespace k3::tok3n::detail {

template <class T>
class span
{
public:
    using value_type = T;

    constexpr span() = default;

    constexpr span(std::span<const T> value)
        : _value(value)
    {}

    template <std::ranges::contiguous_range R>
    requires std::same_as<T, std::ranges::range_value_t<R>>
    constexpr span(R&& r)
        : _value(std::forward<R>(r))
    {}

    template <class... Args>
    requires std::constructible_from<std::span<const T>, Args...>
    constexpr span(Args&&... args)
        : _value(std::forward<Args>(args)...)
    {}

    constexpr const auto* data() const { return _value.data(); }
    constexpr std::size_t size() const { return _value.size(); }
    constexpr bool empty() const { return _value.empty(); }

    constexpr const auto& front() const { return _value.front(); }
    constexpr auto begin() const { return _value.begin(); }
    constexpr auto end() const { return _value.end(); }

    constexpr std::span<const T> first(std::size_t count) const { return { _value.first(count) }; }
    constexpr std::span<const T> subspan(std::size_t offset, std::size_t count = std::dynamic_extent) const { return { _value.subspan(offset, count) }; }

private:
    std::span<const T> _value;
};

template <character T>
class span<T>
{
public:
    using value_type = T;

    constexpr span() = default;

    constexpr span(std::span<const T> value)
        : _value(value)
    {}

    template <std::ranges::contiguous_range R>
    requires std::same_as<T, std::ranges::range_value_t<R>>
    constexpr span(R&& r)
        : _value(std::forward<R>(r))
    {}

    template <class... Args>
    requires std::constructible_from<std::span<const T>, Args...>
    constexpr span(Args&&... args)
        : _value(std::forward<Args>(args)...)
    {}

    constexpr span(std::basic_string_view<T> value)
        : _value(value)
    {}

    constexpr span(const T* data)
        : _value(std::basic_string_view<T>(data))
    {}

    template <std::size_t N>
    constexpr span(const T(&arr)[N])
        : _value(arr, N - 1)
    {}

    constexpr operator std::basic_string_view<T>() const
    {
        return { _value.data(), _value.size() };
    }

    constexpr const auto* data() const { return _value.data(); }
    constexpr std::size_t size() const { return _value.size(); }
    constexpr bool empty() const { return _value.empty(); }

    constexpr const auto& front() const { return _value.front(); }
    constexpr auto begin() const { return _value.begin(); }
    constexpr auto end() const { return _value.end(); }

    constexpr std::span<const T> first(std::size_t count) const { return { _value.first(count) }; }
    constexpr std::span<const T> subspan(std::size_t offset, std::size_t count = std::dynamic_extent) const { return { _value.subspan(offset, count) }; }

private:
    std::span<const T> _value;
};

namespace impl {

template <class T>
concept is_span =
    requires { typename T::value_type; } and
    std::derived_from<T, span<typename T::value_type>>;

} // namespace impl

struct span_equal_to
{
    using is_transparent = void;

    template <class T, class U>
    [[nodiscard]] constexpr bool operator()(const span<T>& lhs, const span<U>& rhs)
    {
        static_assert(equality_comparable_with<T, U>);

        if (lhs.size() != rhs.size())
            return false;

        auto it1 = lhs.begin();
        auto it2 = rhs.begin();
        for (std::size_t i = 0; i != lhs.size(); ++i, ++it1, ++it2)
        {
            if (not (*it1 == *it2))
                return false;
        }
        return true;
    }

    template <class T, class RHS>
    requires (not impl::is_span<std::remove_cvref_t<RHS>>)
    [[nodiscard]] constexpr bool operator()(const span<T>& lhs, RHS&& rhs)
    {
        if constexpr (std::is_bounded_array_v<std::remove_cvref_t<RHS>> or std::is_pointer_v<std::remove_cvref_t<RHS>>)
        {
            return lhs.operator std::basic_string_view<T>() == std::basic_string_view<T>(std::forward<RHS>(rhs));
        }
        else if constexpr (std::ranges::contiguous_range<RHS> and std::same_as<T, std::ranges::range_value_t<RHS>>)
        {
            return operator()(lhs, span<T>(std::forward<RHS>(rhs)));
        }
        else
        {
            static_assert(std::same_as<void, T>, "operator==() not available for `span` and this right-hand type");
            return false;
        }
    }
};

template <class T, class U>
[[nodiscard]] constexpr bool operator==(const span<T>& lhs, const span<U>& rhs)
{
    return span_equal_to{}(lhs, rhs);
}

template <class T, class RHS>
requires (not impl::is_span<std::remove_cvref_t<RHS>>)
[[nodiscard]] constexpr bool operator==(const span<T>& lhs, RHS&& rhs)
{
    return span_equal_to{}(lhs, std::forward<RHS>(rhs));
}

} // namespace k3::tok3n::detail



template <class T>
struct std::equal_to<k3::tok3n::detail::span<T>> : k3::tok3n::detail::span_equal_to {};



namespace k3::tok3n::detail {

template <class T>
class input_span : public span<T>
{
public:
    using span<T>::span;
};

template <std::ranges::contiguous_range R>
input_span(R&&) -> input_span<std::ranges::range_value_t<R>>;
template <character T>
input_span(const T*) -> input_span<T>;

namespace impl {

template <class T>
struct input_value {};

template <std::ranges::contiguous_range R>
struct input_value<R>
{
    using type = std::ranges::range_value_t<R>;
};

template <character T>
struct input_value<const T*>
{
    using type = T;
};

template <class T>
struct input_value<const T> { using type = typename input_value<T>::type; };
template <class T>
struct input_value<T&> { using type = typename input_value<T>::type; };
template <class T>
struct input_value<T&&> { using type = typename input_value<T>::type; };

} // namespace impl

template <class T>
using input_value_t = typename impl::input_value<T>::type;

template <class T, class V>
concept input_constructible_for = equality_comparable_with<input_value_t<T>, V>;

template <class T>
class output_span : public span<T>
{
public:
    using span<T>::span;
};

template <std::ranges::contiguous_range R>
output_span(R&&) -> output_span<std::ranges::range_value_t<R>>;
template <character T>
output_span(const T*) -> output_span<T>;

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_SPAN_HPP
