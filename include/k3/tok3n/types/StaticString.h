#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>

namespace k3::tok3n {

template <class T, std::size_t N>
struct StaticArray
{
	std::array<T, N + 1> data = {};

	constexpr StaticArray() = default;

	constexpr StaticArray(const T(&input)[N + 1]) noexcept
	{
		std::ranges::copy_n(input, N + 1, data.begin());
	}

	constexpr StaticArray(T c) noexcept requires (N == 1)
	{
		data[0] = c;
	}

	constexpr std::span<const T> span() const
	{
		return { data.data(), N };
	}

	constexpr bool contains(const T& t) const
	{
		for (const auto& element : data)
			if (element == t)
				return true;
		return false;
	}

	constexpr auto begin() const { return data.begin(); }
	constexpr auto begin()       { return data.begin(); }
	constexpr auto end()   const { return data.end() - 1; }
	constexpr auto end()         { return data.end() - 1; }

	consteval std::size_t size() const noexcept { return N; }
	
	using value_type = T;
};

template <class T, std::size_t N>
StaticArray(const T(&)[N]) -> StaticArray<T, N - 1>;

template <class T>
StaticArray(T) -> StaticArray<T, 1>;



template <std::size_t N>
using StaticString = StaticArray<char, N>;

template <std::size_t N>
StaticArray(const char(&)[N]) -> StaticArray<char, N - 1>;

StaticArray(char) -> StaticArray<char, 1>;



template <class T, std::size_t N>
consteval bool is_sorted_and_uniqued(const StaticArray<T, N>& str)
{
	if constexpr (N <= 1)
		return true;
	else
	{
		for (std::size_t i = 0; i < N - 1; ++i)
			if (str.data[i] >= str.data[i + 1])
				return false;
		return true;
	}
}

template <StaticArray str> // Must be a template parameter because the return type depends on it
consteval auto sort_and_unique()
{
	if constexpr (is_sorted_and_uniqued(str))
		return str;

	else
	{
		constexpr auto histogram = []
		{
			std::array<bool, 128> arr{}; // Histogram
			for (char c : str)
				arr[static_cast<std::size_t>(c)] = true;
			return arr;
		}();

		constexpr auto N = std::ranges::count(histogram, true);

		StaticArray<typename decltype(str)::value_type, N> out{};
		auto it = out.begin();
		for (std::size_t i = 0; i != 128; ++i)
		{
			if (histogram[i])
				*it++ = static_cast<char>(i);
		}

		return out;
	}
}



template <class T, std::size_t M, std::size_t N >
constexpr bool operator==(const StaticArray<T, M>& lhs, const StaticArray<T, N>& rhs)
{
	if constexpr (M != N)
		return false;
	else
		return lhs.data == rhs.data;
}

template <class T, std::size_t M, std::size_t N>
constexpr StaticArray<T, M + N> operator+(const StaticArray<T, M>& lhs, const StaticArray<T, N>& rhs)
{
	StaticArray<T, M + N> str;
	std::ranges::copy(lhs, str.begin());
	std::ranges::copy(rhs, str.begin() + M);
	return str;
}

} // namespace k3::tok3n
