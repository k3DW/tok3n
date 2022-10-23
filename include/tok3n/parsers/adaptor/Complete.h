#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
struct Complete
{
	using result_type = typename P::result_type;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (not result.has_value() or result.remaining() != "")
			return { failure, input };
		else
			return result;
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
