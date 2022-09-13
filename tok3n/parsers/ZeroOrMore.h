#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <Parser P>
struct ZeroOrMore
{
	static constexpr Result parse(Input input)
	{
		const Input original_input = input;

		std::vector<Result> results;
		while (true)
		{
			Result result = P::parse(input);
			if (result.has_value())
			{
				input = result.remainder();
				results.emplace_back(std::move(result));
				continue;
			}
			else
				break;
		}

		return Result::success(results, input);
	}
};

template <Parser P>
struct NewZeroOrMore
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr NewResult<result_type> parse(Input input)
	{
		const Input original_input = input;

		result_type results;
		while (true)
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				results.emplace_back(std::move(result.value()));
				continue;
			}
			else
				break;
		}

		return { success, std::move(results), input };
	}
};

}
