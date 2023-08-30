#pragma once
#include <format>
#include <string>
#include <string_view>
#include <vector>

class StringBuilder
{
public:
	constexpr StringBuilder() = default;

	template <class T>
	constexpr void append(T&& t)
	{
		pieces.emplace_back(std::forward<T>(t));
	}

	template <class... Args>
	constexpr void format(const std::format_string<Args...> fmt, Args&&... args)
	{
		pieces.emplace_back(std::format(fmt, std::forward<Args>(args)...));
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
	std::vector<std::string> pieces;
};
