#pragma once
#include <algorithm>
#include <ostream>
#include <span>
#include <string_view>
#include <k3/tok3n/concepts/CharType.h>
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

	template <class... Args>
	requires std::constructible_from<std::span<const T>, Args...>
	constexpr Span(Args&&... args)
		: _value(std::forward<Args>(args)...)
	{}

	constexpr Span(std::basic_string_view<T> value) requires CharType<T>
		: _value(value)
	{}
	
	constexpr Span(const T* data) requires CharType<T>
		: _value(std::basic_string_view<T>(data))
	{}

	template <std::size_t N>
	constexpr Span(const T(&arr)[N]) requires CharType<T>
		: _value(arr, N - 1)
	{}

	constexpr operator std::basic_string_view<T>() const requires CharType<T>
	{
		return { _value.data(), _value.size() };
	}

	constexpr const T* data() const { return _value.data(); }
	constexpr std::size_t size() const { return _value.size(); }
	constexpr bool empty() const { return _value.empty(); }

	constexpr const T& front() const { return _value.front(); }
	constexpr auto begin() const { return _value.begin(); }
	constexpr auto end() const { return _value.end(); }

	constexpr Span first(std::size_t count) const { return { _value.first(count) }; }
	constexpr Span subspan(std::size_t offset, std::size_t count = std::dynamic_extent) const { return { _value.subspan(offset, count) }; }

	template <class U>
	requires requires (T t, U u) { { t == u } -> std::convertible_to<bool>; }
	friend constexpr bool operator==(const Span& lhs, const Span<U, Tag>& rhs)
	{
		return std::ranges::equal(lhs._value, rhs._value);
	}

	template <class U>
	friend std::basic_ostream<U>& operator<<(std::basic_ostream<U>& os, Span span)
	{
		if constexpr (CharType<T>)
			return os << U{ '"' } << span.operator std::basic_string_view<T>() << U{ '"' };
		else
		{
			os << U{ '[' };
			auto it = span.begin();
			const auto end = span.end();
			if (it != end)
				os << *it++;
			while (it != end)
				os << U{ ',' } << U{ ' ' } << *it++;
			return os << U{ ']' };
		}
	}

private:
	std::span<const T> _value;

	template <class U, class Uag>
	friend class Span;
};

template <class T>
using Input = Span<T, InputSpanTag>;

template <class T>
using Output = Span<T, OutputSpanTag>;

} // namespace k3::tok3n
