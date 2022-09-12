#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

struct ChoiceExec
{
	Input input;
	Result& result_ref;

	template <Parser P>
	constexpr bool operator()(P) const
	{
		Result result = P::parse(input);
		if (result.has_value())
		{
			result_ref = std::move(result);
			return true;
		}
		else
			return false;
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Choice
{
	static constexpr Result parse(Input input)
	{
		Result result = Result::failure(input);
		const auto executor = ChoiceExec{ .input = input, .result_ref = result };
		(... || executor(Ps{}));

		return result;
	}
};

}
