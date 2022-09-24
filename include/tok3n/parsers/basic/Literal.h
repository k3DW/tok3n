#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

BEGIN_NAMESPACE_TOK3N()

template <static_string str>
requires (str.ascii()) && (str.size() != 0)
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

END_NAMESPACE_TOK3N()
