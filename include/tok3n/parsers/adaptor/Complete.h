#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/types/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
struct Complete
{
	using result_type = typename P::result_type;

	static constexpr ParserType type = ParserType::Complete;

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
		auto result = P::lookahead(input);
		if (not result.has_value() or result.remaining() != "")
			return { failure, input };
		else
			return result;
	}
};

TOK3N_END_NAMESPACE()
