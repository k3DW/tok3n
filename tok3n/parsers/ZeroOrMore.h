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

}
