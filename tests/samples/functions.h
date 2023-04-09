#pragma once
#include <tok3n/tok3n.h>

TOK3N_BEGIN_NAMESPACE(tests::samples::functions)

constexpr std::size_t func1(std::vector<std::string_view>&& vec)
{
	return vec.size();
}

constexpr auto func2 = [](const std::optional<std::string_view>& opt) -> std::vector<char>
{
	if (not opt.has_value())
		return {};
	else
	{
		auto& sv = *opt;
		return { sv.begin(), sv.end() };
	}
};

constexpr struct func3_t
{
	constexpr bool operator()(std::tuple<std::string_view, std::vector<std::string_view>>&& tup) const
	{
		auto&& [sv, vec] = std::move(tup);
		return vec.size() % 2 == 0;
	}
} func3;

constexpr struct func3_apply_t
{
	constexpr bool operator()(std::string_view, std::vector<std::string_view>&& vec) const
	{
		return vec.size() % 2 == 0;
	}
} func3_apply;

struct func4
{
	constexpr func4(int multiply_by)
		: multiply_by(multiply_by) {}

	int multiply_by;

	constexpr std::size_t operator()(const std::tuple<std::vector<std::string_view>, std::optional<std::string_view>>& tup) const
	{
		const auto& [vec, opt] = tup;
		return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};

struct func4_apply
{
	constexpr func4_apply(int multiply_by)
		: multiply_by(multiply_by) {}

	int multiply_by;

	constexpr std::size_t operator()(const std::vector<std::string_view>& vec, const std::optional<std::string_view>& opt) const
	{
		return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};

constexpr auto sink_func = [](auto&&...) {};

TOK3N_END_NAMESPACE(tests::samples::functions)
