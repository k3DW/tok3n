#pragma once

constexpr std::size_t func1(std::vector<Output<char>>&& vec)
{
	return vec.size();
}

constexpr auto func2 = [](const std::optional<Output<char>>& opt) -> std::vector<char>
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
	constexpr bool operator()(std::tuple<Output<char>, std::vector<Output<char>>>&& tup) const
	{
		auto&& [sv, vec] = std::move(tup);
		return vec.size() % 2 == 0;
	}
} func3;

constexpr struct func3_apply_t
{
	constexpr bool operator()(Output<char>, std::vector<Output<char>>&& vec) const
	{
		return vec.size() % 2 == 0;
	}
} func3_apply;

struct func4
{
	constexpr func4(int multiply_by)
		: multiply_by(multiply_by) {}

	int multiply_by;

	constexpr std::size_t operator()(const std::tuple<std::vector<Output<char>>, std::optional<Output<char>>>& tup) const
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

	constexpr std::size_t operator()(const std::vector<Output<char>>& vec, const std::optional<Output<char>>& opt) const
	{
		return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};

constexpr auto sink_func = [](auto&&...) {};
