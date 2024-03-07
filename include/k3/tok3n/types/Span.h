#pragma once
#include <algorithm>
#include <span>
#include <string_view>
#include <k3/tok3n/concepts/CharType.h>
#include <k3/tok3n/concepts/EqualityComparableWith.h>
#include <k3/tok3n/types/Tags.h>

namespace k3::tok3n {

template <class T, class Tag>
class Span
{
public:
	constexpr Span() = default;

	constexpr Span(std::span<const T> value)
		: _value(value)
	{}

	template <std::ranges::contiguous_range R>
	requires std::same_as<T, std::ranges::range_value_t<R>>
	constexpr Span(R&& r)
		: _value(std::forward<R>(r))
	{}

	template <class... Args>
	requires std::constructible_from<std::span<const T>, Args...>
	constexpr Span(Args&&... args)
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

template <CharType T, class Tag>
class Span<T, Tag>
{
public:
	constexpr Span() = default;

	constexpr Span(std::span<const T> value)
		: _value(value)
	{}

	template <std::ranges::contiguous_range R>
	requires std::same_as<T, std::ranges::range_value_t<R>>
	constexpr Span(R&& r)
		: _value(std::forward<R>(r))
	{}

	template <class... Args>
	requires std::constructible_from<std::span<const T>, Args...>
	constexpr Span(Args&&... args)
		: _value(std::forward<Args>(args)...)
	{}

	constexpr Span(std::basic_string_view<T> value)
		: _value(value)
	{}
	
	constexpr Span(const T* data)
		: _value(std::basic_string_view<T>(data))
	{}

	template <std::size_t N>
	constexpr Span(const T(&arr)[N])
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

namespace detail {

template <class S>
static constexpr bool is_span_v = false;
template <class T, class Tag>
static constexpr bool is_span_v<Span<T, Tag>> = true;
template <class S>
static constexpr bool is_span_v<const S> = is_span_v<S>;
template <class S>
static constexpr bool is_span_v<S&> = is_span_v<S>;
template <class S>
static constexpr bool is_span_v<S&&> = is_span_v<S>;

} // namespace detail

template <class T, class Tag, class U>
requires EqualityComparableWith<T, U>
constexpr bool operator==(const Span<T, Tag>& lhs, const Span<U, Tag>& rhs)
{
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

template <class T, class Tag, class RHS>
requires (not detail::is_span_v<RHS>)
constexpr bool operator==(const Span<T, Tag>& lhs, RHS&& rhs)
{
	if constexpr (CharType<T> and std::is_bounded_array_v<std::remove_cvref_t<RHS>>)
	{
		return std::basic_string_view<T>(lhs) == std::basic_string_view<T>(std::forward<RHS>(rhs));
	}
	else if constexpr (CharType<T> and std::is_pointer_v<std::remove_cvref_t<RHS>>)
	{
		return std::basic_string_view<T>(lhs) == std::basic_string_view<T>(std::forward<RHS>(rhs));
	}
	else if constexpr (std::ranges::contiguous_range<RHS> && std::same_as<T, std::ranges::range_value_t<RHS>>)
	{
		return lhs == Span<T, Tag>(std::forward<RHS>(rhs));
	}
	else
	{
		static_assert(std::same_as<void, T>, "operator==() not available for Span and this right-hand type");
		return false;
	}
}

template <class T>
using Input = Span<T, InputSpanTag>;

template <class T>
using Output = Span<T, OutputSpanTag>;

} // namespace k3::tok3n
