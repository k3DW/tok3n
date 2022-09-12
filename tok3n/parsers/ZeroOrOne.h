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

}
