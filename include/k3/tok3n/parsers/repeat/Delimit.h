#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, ParserCompatibleWith<P> D, IsConst<bool> KeepDelimiters>
struct Delimit
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::conditional_t<KeepDelimiters::value,
		std::pair<std::vector<typename P::template result_for<V>>, std::vector<typename D::template result_for<V>>>,
		std::vector<typename P::template result_for<V>>
	>;

	static constexpr ParserFamily family = DelimitFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input) requires (not KeepDelimiters::value)
	{
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Delimit's child parser's result for the given value cannot be void.");
			
		result_for<value_type> results;

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

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input) requires (KeepDelimiters::value)
	{
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Delimit's child parser's result for the given value cannot be void.");
		static_assert(not std::same_as<typename D::template result_for<value_type>, void>,
			"Delimit(keep)'s delimiter parser's result for the given value cannot be void.");

		result_for<value_type> results;
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
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Delimit's child parser's result for the given value cannot be void.");
		static_assert(not KeepDelimiters::value or not std::same_as<typename D::template result_for<value_type>, void>,
			"Delimit(keep)'s delimiter parser's result for the given value cannot be void.");

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
