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
	std::array<T, N> data = {};

	constexpr StaticArray() = default;

	template <class... Ts>
	requires (sizeof...(Ts) == N - 1) and (... and std::convertible_to<Ts, T>)
	constexpr StaticArray(T t, Ts... ts)
		: data(t, ts...)
	{}

	constexpr StaticArray(const T(&input)[N + 1]) noexcept requires CharType<T>
	{
		std::ranges::copy_n(input, N, data.begin());
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
	constexpr auto end()   const { return data.end(); }
	constexpr auto end()         { return data.end(); }

	consteval std::size_t size() const noexcept { return N; }
	
	using value_type = T;

	template <std::size_t M>
	static constexpr auto create_empty_with_size = StaticArray<T, M>{};
};

template <class T, class... Ts>
requires (... and std::convertible_to<Ts, T>)
StaticArray(T, Ts...) -> StaticArray<T, sizeof...(Ts) + 1>;

template <CharType T, std::size_t N>
StaticArray(const T(&)[N]) -> StaticArray<T, N - 1>;

template <class T>
StaticArray(T) -> StaticArray<T, 1>;



template <StaticArray lhs, StaticArray rhs>
concept LikeStaticArrays = std::same_as<typename decltype(lhs)::value_type, typename decltype(rhs)::value_type>;



template <class T, std::size_t N>
constexpr bool is_sorted_and_uniqued(const StaticArray<T, N>& str)
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
		constexpr auto sorted = []
		{
			auto copy = str;
			std::ranges::sort(copy);
			return copy;
		}();

		constexpr auto pair = []
		{
			auto copy = sorted;
			auto subrange = std::ranges::unique(copy);
			auto new_size = subrange.begin() - copy.begin();
			return std::make_pair(std::move(copy), new_size);
		}();

		auto out = str.create_empty_with_size<pair.second>;
		std::ranges::copy_n(pair.first.begin(), pair.second, out.begin());
		return out;
	}
}



template <class T, std::size_t M, std::size_t N>
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
