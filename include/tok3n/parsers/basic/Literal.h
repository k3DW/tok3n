#pragma once
#include "tok3n/parsers/Details.h"
#include "tok3n/types.h"
#include "tok3n/concepts.h"

TOK3N_BEGIN_NAMESPACE()

template <static_string str>
requires detail::Literal_able<str>
struct Literal
{
	using result_type = Input;

	static constexpr ParserType type = ParserType::Literal;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || not input.starts_with(str.view()))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + str.size() }, { begin + str.size(), input.end() } };
		}
	}

	static constexpr Result<void> lookahead(Input input)
	{
		if (input.empty() || not input.starts_with(str.view()))
			return { failure, input };
		else
		{
			input.remove_prefix(str.size());
			return { success, input };
		}
	}
};

TOK3N_END_NAMESPACE()
