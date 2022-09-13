#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <Parser P>
struct ZeroOrOne
{
	static constexpr Result parse(Input input)
	{
		Result result = P::parse(input);
		if (result.has_value())
			return result;
		else
			return Result::success("", input);
	}
};

template <Parser P>
struct NewZeroOrOne
{
	using result_type = std::optional<typename P::result_type>;

	static constexpr NewResult<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, result_type{ std::move(result.value()) }, result.remaining() };
		else
			return { success, std::nullopt, input };
	}
};

}
