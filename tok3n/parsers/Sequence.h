#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

struct SequenceExec
{
	Input& input;
	std::vector<Result>& results;

	template <Parser P>
	constexpr bool operator()(P) const
	{
		Result result = P::parse(input);
		if (result.has_value())
		{
			input = result.remainder();
			results.emplace_back(std::move(result));
			return true;
		}
		else
			return false;
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Sequence
{
	static constexpr Result parse(Input input)
	{
		const Input original_input = input;

		std::vector<Result> results;
		const auto executor = SequenceExec{ .input = input, .results = results };
		(... && executor(Ps{}));

		if (results.size() == sizeof...(Ps))
			return Result::success(results, input);
		else
			return Result::failure(original_input);
	}
};

}
