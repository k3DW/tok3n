#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

BEGIN_NAMESPACE_TOK3N()

template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii()) && (str.size() != 0)
struct NotChar
{
	using result_type = std::string_view;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || str.contains(input.front()))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + 1 }, { begin + 1, input.end() } };
		}
	}

	static constexpr Result<void> lookahead(Input input)
	{
		if (input.empty() || str.contains(input.front()))
			return { failure, input };
		else
		{
			input.remove_prefix(1);
			return { success, input };
		}
	}
};

END_NAMESPACE_TOK3N()
