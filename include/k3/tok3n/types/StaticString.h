#pragma once
#include <tok3n/namespace.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>

// Ideas mostly taken from CTRE

TOK3N_BEGIN_NAMESPACE()

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
		return view().contains(c);
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
consteval bool is_ascii(const StaticString<N>& str)
{
	constexpr auto pred = [](char c) -> bool { return (c & 0x80) == 0; };
	return std::ranges::all_of(str.view(), pred);
}

template <std::size_t N>
consteval bool is_unique_and_sorted(const StaticString<N>& str)
{
	if constexpr (N == 1)
		return true;
	else
	{
		constexpr auto less = [](std::span<const char> span) -> bool { return span[0] < span[1]; };
		return std::ranges::all_of(str.view() | std::views::slide(2), less);
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

TOK3N_END_NAMESPACE()
