#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, Parser D, detail::is_integral_constant<bool> KeepDelimiters>
requires DelimitConstructible<P, D, KeepDelimiters>
struct Delimit
{
	using result_type = std::conditional_t<KeepDelimiters::value,
		std::pair<std::vector<typename P::result_type>, std::vector<typename D::result_type>>,
		std::vector<typename P::result_type>
	>;

	static constexpr ParserType type = DelimitType;

	static constexpr Result<result_type> parse(Input input) requires (not KeepDelimiters::value)
	{
		result_type results;

		auto result = P::parse(input);
		if (not result.has_value())
			return { failure, input };

		while (result)
		{
			input = result.remaining();
			results.emplace_back(std::move(*result));

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			result = P::parse(delimit_result.remaining());
		}

		return { success, std::move(results), input };
	}

	static constexpr Result<result_type> parse(Input input) requires (KeepDelimiters::value)
	{
		result_type results;
		auto& [values, delimiters] = results;

		auto result = P::parse(input);
		if (not result.has_value())
			return { failure, input };

		while (result)
		{
			input = result.remaining();
			values.emplace_back(std::move(*result));

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			result = P::parse(delimit_result.remaining());
			if (result)
				delimiters.emplace_back(std::move(*delimit_result));
		}

		return { success, std::move(results), input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		auto result = P::lookahead(input);
		if (not result.has_value())
			return { failure, input };

		while (result)
		{
			input = result.remaining();

			auto delimit_result = D::lookahead(input);
			if (not delimit_result)
				break;

			result = P::lookahead(delimit_result.remaining());
		}

		return { success, input };
	}
};

} // namespace k3::tok3n
