#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>

namespace k3
{

template <std::size_t N>
struct static_string
{
	std::array<char, N> data = {};

	constexpr static_string() = default;

	constexpr static_string(const char(&input)[N + 1]) noexcept
	{
		std::ranges::copy_n(input, N, data.begin());
	}

	constexpr static_string(char c) noexcept requires (N == 1)
	{
		data[0] = c;
	}

	constexpr bool contains(char c) const noexcept
	{
		return std::string_view(data.data(), N).contains(c);
	}

	constexpr auto begin() const { return data.begin(); }
	constexpr auto begin()       { return data.begin(); }
	constexpr auto end()   const { return data.end(); }
	constexpr auto end()         { return data.end(); }

	consteval std::size_t size() const noexcept { return N; }

	constexpr bool ascii() const
	{
		return std::ranges::all_of(data, [](char c) -> bool { return (c & 0x80) == 0; });
	}

	constexpr bool unique_and_sorted() const
	{
		if constexpr (N == 1)
			return true;
		else
		{
			constexpr auto less = [](auto&& span) -> bool { return span[0] < span[1]; };
			return std::ranges::all_of(data | std::views::slide(2), less);
		}
	}
};

template <std::size_t N>
static_string(const char(&)[N]) -> static_string<N - 1>;

static_string(char) -> static_string<1>;



template <std::size_t M, std::size_t N>
constexpr bool operator==(const static_string<M>& lhs, const static_string<N>& rhs)
{
	if constexpr (M != N)
		return false;
	else
		return lhs.data == rhs.data;
}

template <std::size_t M, std::size_t N>
constexpr static_string<M + N> operator+(const static_string<M>& lhs, const static_string<N>& rhs)
{
	static_string<M + N> str;
	std::ranges::copy(lhs, str.begin());
	std::ranges::copy(rhs, str.begin() + M);
	return str;
}



constexpr static_string every_char = []() consteval -> static_string<128>
{
	static_string<128> str;
	for (int c = 0; c < 128; c++)
		str.data[c] = c;
	return str;
}();

template <static_string str>
constexpr auto every_char_except = []()
{
	static_string<128 - str.size()> output;
	auto it = output.data.begin();

	std::string_view sv = { str.begin(), str.end() };
	for (int c = 0; c < 128; c++)
	{
		if (not sv.contains(c))
			*it++ = c;
	}

	return output;
}();

template <std::size_t N>
requires (N > 0 && N < 128)
constexpr static_string<128 - N> inverse_string(const static_string<N>& str)
{
	static_string<128 - N> output;
	auto it = output.data.begin();

	std::string_view sv = { str.begin(), str.end() };
	for (int c = 0; c < 128; c++)
	{
		if (not sv.contains(c))
			*it++ = c;
	}

	return output;
}

}
