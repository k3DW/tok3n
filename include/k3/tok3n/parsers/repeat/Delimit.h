#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, Parser D, IsConst<bool> KeepDelimiters>
requires DelimitConstructible<P, D, KeepDelimiters>
struct Delimit
{
	using value_type = typename P::value_type;
	using result_type = std::conditional_t<KeepDelimiters::value,
		std::pair<std::vector<typename P::result_type>, std::vector<typename D::result_type>>,
		std::vector<typename P::result_type>
	>;

	static constexpr ParserFamily family = DelimitFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input) requires (not KeepDelimiters::value)
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

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input) requires (KeepDelimiters::value)
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

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
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
