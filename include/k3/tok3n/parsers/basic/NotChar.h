#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <StaticString str>
requires (is_ascii(str)) and (is_sorted_and_uniqued(str))
struct NotChar
{
	using result_type = Input;

	static constexpr ParserType type = NotCharType;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || str.contains(input.front()))
			return { failure, input };
		else
		{
			const auto data = input.data();
			return { success, { data, 1 }, { data + 1, input.size() - 1 } };
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

TOK3N_END_NAMESPACE()
