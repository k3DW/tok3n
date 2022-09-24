#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

BEGIN_NAMESPACE_TOK3N()

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

END_NAMESPACE_TOK3N()
