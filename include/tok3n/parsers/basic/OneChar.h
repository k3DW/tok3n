#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/types/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <static_string str>
requires detail::SingleChar_able<str>
struct OneChar
{
	using result_type = Input;

	static constexpr ParserType type = ParserType::OneChar;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || not str.contains(input.front()))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + 1 }, { begin + 1, input.end() } };
		}
	}

	static constexpr Result<void> lookahead(Input input)
	{
		if (input.empty() || not str.contains(input.front()))
			return { failure, input };
		else
		{
			input.remove_prefix(1);
			return { success, input };
		}
	}
};

TOK3N_END_NAMESPACE()
