#pragma once
#include <string>
#include <string_view>
#include <vector>

class StringBuilder
{
public:
	constexpr StringBuilder() = default;

	template <class... Ts>
	constexpr void append(Ts&&... ts)
	{
		(append_impl(std::forward<Ts>(ts)), ...);
	}

	std::string build() &&
	{
		const size_t size = [&]
		{
			size_t total = 0;
			for (const auto& piece : pieces)
				total += piece.size();
			return total;
		}();

		std::string out;
		out.reserve(size);

		for (const auto& piece : pieces)
			out.insert(out.end(), piece.begin(), piece.end());
		return out;
	}

private:
	template <class T>
	constexpr void append_impl(T&& t)
	{
		if constexpr (std::integral<std::remove_cvref_t<T>>)
			pieces.emplace_back(std::to_string(t));
		else
			pieces.emplace_back(std::forward<T>(t));
	}

	std::vector<std::string> pieces;
};
