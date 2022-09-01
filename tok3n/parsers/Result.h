#pragma once
#include <string_view>
#include <variant>
#include <vector>

namespace k3::parser
{

class Result
{
public:
	static constexpr Result failure(std::string_view remaining)
	{
		return Result(std::monostate{}, remaining);
	}

	static constexpr Result success(std::string_view result, std::string_view remaining)
	{
		return Result(result, remaining);
	}

	static constexpr Result success(std::vector<Result>& results, std::string_view remaining)
	{
		return Result(std::move(results), remaining);
	}

	constexpr bool empty()     const noexcept { return std::holds_alternative<std::monostate>(result); }
	constexpr bool has_value() const noexcept { return not std::holds_alternative<std::monostate>(result); }
	constexpr operator bool()  const noexcept { return not std::holds_alternative<std::monostate>(result); }

	constexpr bool holds_string_view() const noexcept { return std::holds_alternative<std::string_view>(result); }
	constexpr auto get_string_view()   const { return std::get<std::string_view>(result); }

	constexpr bool  holds_vector() const noexcept { return std::holds_alternative<std::vector<Result>>(result); }
	constexpr auto& get_vector()   const { return std::get<std::vector<Result>>(result); }

	constexpr std::string_view remainder() const noexcept { return remaining; }

	constexpr const char* begin() const noexcept;
	constexpr const char* end()   const noexcept;

	constexpr std::string_view flatten() const noexcept { return std::string_view{ begin(), end() }; }

private:
	Result() = delete;

	template <class T>
	constexpr Result(T&& result, std::string_view remaining) : result(std::forward<T>(result)), remaining(remaining) {}

	using variant = std::variant<std::monostate, std::string_view, std::vector<Result>>;

	variant          result;
	std::string_view remaining;
};

constexpr const char* Result::begin() const noexcept
{
	if (holds_string_view())
		return get_string_view().data();
	else if (holds_vector())
	{
		const auto& vector = get_vector();
		for (auto it = vector.begin(); it != vector.end(); it++)
		{
			const char* begin = it->begin();
			if (begin != nullptr)
				return begin;
		}
	}

	return nullptr;
}

constexpr const char* Result::end() const noexcept
{
	if (holds_string_view())
	{
		auto sv = get_string_view();
		return sv.data() + sv.size();
	}
	else if (holds_vector())
	{
		const auto& vector = get_vector();
		for (auto it = vector.rbegin(); it != vector.rend(); it++)
		{
			const char* begin = it->end();
			if (begin != nullptr)
				return begin;
		}
	}

	return nullptr;
}

}
