constexpr std::size_t func1(std::vector<k3::tok3n::detail::output_span<::value_type>>&& vec)
{
	return vec.size();
}

constexpr auto func2 = []<class T>(const std::optional<k3::tok3n::detail::output_span<T>>& opt) -> std::vector<T>
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
	constexpr bool operator()(std::tuple<k3::tok3n::detail::output_span<char>, std::vector<k3::tok3n::detail::output_span<char>>>&& tup) const
	{
		auto&& [sv, vec] = std::move(tup);
		return vec.size() % 2 == 0;
	}

	constexpr bool operator()(std::tuple<k3::tok3n::detail::output_span<wchar_t>, std::vector<k3::tok3n::detail::output_span<wchar_t>>>&& tup) const
	{
		auto&& [sv, vec] = std::move(tup);
		return vec.size() % 2 == 0;
	}

	constexpr bool operator()(std::tuple<k3::tok3n::detail::output_span<int>, std::vector<k3::tok3n::detail::output_span<int>>>&& tup) const
	{
		auto&& [sv, vec] = std::move(tup);
		return vec.size() % 2 == 0;
	}
} func3;

constexpr struct func3_apply_t
{
	constexpr bool operator()(k3::tok3n::detail::output_span<char>, std::vector<k3::tok3n::detail::output_span<char>>&& vec) const
	{
		return vec.size() % 2 == 0;
	}

	constexpr bool operator()(k3::tok3n::detail::output_span<wchar_t>, std::vector<k3::tok3n::detail::output_span<wchar_t>>&& vec) const
	{
		return vec.size() % 2 == 0;
	}

	constexpr bool operator()(k3::tok3n::detail::output_span<int>, std::vector<k3::tok3n::detail::output_span<int>>&& vec) const
	{
		return vec.size() % 2 == 0;
	}
} func3_apply;

struct func4
{
	constexpr func4(int multiply_by)
		: multiply_by(multiply_by) {}

	int multiply_by;

	constexpr std::size_t operator()(const std::tuple<std::vector<k3::tok3n::detail::output_span<char>>, std::optional<k3::tok3n::detail::output_span<char>>>& tup) const
	{
		const auto& [vec, opt] = tup;
		return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}

	constexpr std::size_t operator()(const std::tuple<std::vector<k3::tok3n::detail::output_span<wchar_t>>, std::optional<k3::tok3n::detail::output_span<wchar_t>>>& tup) const
	{
		const auto& [vec, opt] = tup;
		return multiply_by * vec.size() * (not opt ? 1 : *opt == L"abc" ? 2 : 3);
	}

	constexpr std::size_t operator()(const std::tuple<std::vector<k3::tok3n::detail::output_span<int>>, std::optional<k3::tok3n::detail::output_span<int>>>& tup) const
	{
		const auto& [vec, opt] = tup;
		return multiply_by * vec.size() * (not opt ? 1 : *opt == e<int>("abc") ? 2 : 3);
	}
};

struct func4_apply
{
	constexpr func4_apply(int multiply_by)
		: multiply_by(multiply_by) {}

	int multiply_by;

	constexpr std::size_t operator()(const std::vector<k3::tok3n::detail::output_span<char>>& vec, const std::optional<k3::tok3n::detail::output_span<char>>& opt) const
	{
		return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}

	constexpr std::size_t operator()(const std::vector<k3::tok3n::detail::output_span<wchar_t>>& vec, const std::optional<k3::tok3n::detail::output_span<wchar_t>>& opt) const
	{
		return multiply_by * vec.size() * (not opt ? 1 : *opt == L"abc" ? 2 : 3);
	}

	constexpr std::size_t operator()(const std::vector<k3::tok3n::detail::output_span<int>>& vec, const std::optional<k3::tok3n::detail::output_span<int>>& opt) const
	{
		return multiply_by * vec.size() * (not opt ? 1 : *opt == e<int>("abc") ? 2 : 3);
	}
};

constexpr auto sink_func = [](auto&&...) {};
