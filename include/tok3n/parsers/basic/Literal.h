#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <static_string str>
requires string_usable_in_basic_parser<str>
struct Literal
{
	using result_type = Input;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || not input.starts_with({ str.begin(), str.end() }))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + str.size() }, { begin + str.size(), input.end() } };
		}
	}

	static constexpr Result<void> lookahead(Input input)
	{
		if (input.empty() || not input.starts_with({ str.begin(), str.end() }))
			return { failure, input };
		else
		{
			input.remove_prefix(str.size());
			return { success, input };
		}
	}
};

TOK3N_END_NAMESPACE()
