#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>

// Ideas mostly taken from CTRE

namespace k3::tok3n {

template <std::size_t N>
struct StaticString
{
	std::array<char, N + 1> data = {};

	constexpr StaticString() = default;

	constexpr StaticString(const char(&input)[N + 1]) noexcept
	{
		std::ranges::copy_n(input, N + 1, data.begin());
	}

	constexpr StaticString(char c) noexcept requires (N == 1)
	{
		data[0] = c;
	}

	constexpr std::string_view view() const noexcept
	{
		return std::string_view(data.data(), N);
	}

	constexpr bool contains(char c) const noexcept
	{
		return view().find(c) != std::string_view::npos;
	}

	constexpr auto begin() const { return data.begin(); }
	constexpr auto begin()       { return data.begin(); }
	constexpr auto end()   const { return data.end() - 1; }
	constexpr auto end()         { return data.end() - 1; }

	consteval std::size_t size() const noexcept { return N; }
};

template <std::size_t N>
StaticString(const char(&)[N]) -> StaticString<N - 1>;

StaticString(char) -> StaticString<1>;



template <std::size_t N>
consteval bool is_sorted_and_uniqued(const StaticString<N>& str)
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

template <StaticString str> // Must be a template parameter because the return type depends on it
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

		StaticString<N> out{};
		auto it = out.begin();
		for (std::size_t i = 0; i != 128; ++i)
		{
			if (histogram[i])
				*it++ = static_cast<char>(i);
		}

		return out;
	}
}



template <std::size_t M, std::size_t N>
constexpr bool operator==(const StaticString<M>& lhs, const StaticString<N>& rhs)
{
	if constexpr (M != N)
		return false;
	else
		return lhs.data == rhs.data;
}

template <std::size_t M, std::size_t N>
constexpr StaticString<M + N> operator+(const StaticString<M>& lhs, const StaticString<N>& rhs)
{
	StaticString<M + N> str;
	std::ranges::copy(lhs, str.begin());
	std::ranges::copy(rhs, str.begin() + M);
	return str;
}

} // namespace k3::tok3n
