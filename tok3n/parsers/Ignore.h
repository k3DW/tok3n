#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::tok3n
{

template <Parser P>
struct Ignore
{
	using result_type = void;

	static constexpr Result<result_type> parse(Input input)
	{
		return P::lookahead(input);
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

}
