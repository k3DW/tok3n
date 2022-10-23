#pragma once
#include "tok3n/utilities/namespace.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>

// Ideas mostly taken from CTRE

TOK3N_BEGIN_NAMESPACE()

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
};

template <std::size_t N>
static_string(const char(&)[N]) -> static_string<N - 1>;

static_string(char) -> static_string<1>;



constexpr bool is_ascii(char c)
{
	return (c & 0x80) == 0;
}

template <std::size_t N>
constexpr bool is_ascii(const static_string<N>& str)
{
	using type_ = bool(*)(char);
	return std::ranges::all_of(str.data, static_cast<type_>(is_ascii));
}

template <std::size_t N>
constexpr bool is_unique_and_sorted(const static_string<N>& str)
{
	if constexpr (N == 1)
		return true;
	else
	{
		constexpr auto less = [](std::span<const char> span) -> bool { return span[0] < span[1]; };
		return std::ranges::all_of(str.data | std::views::slide(2), less);
	}
}



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
	for (std::size_t c = 0; c < 128; c++)
		str.data[c] = static_cast<char>(c);
	return str;
}();

TOK3N_END_NAMESPACE()
