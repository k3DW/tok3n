#pragma once
#include "tok3n/parsers/Details.h"
#include "tok3n/types.h"
#include "tok3n/concepts.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
struct Ignore
{
	using result_type = void;

	static constexpr ParserType type = ParserType::Ignore;

	static constexpr Result<result_type> parse(Input input)
	{
		return P::lookahead(input);
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
