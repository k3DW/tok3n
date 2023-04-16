#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <StaticString str>
requires (is_ascii(str))
struct Literal
{
	using result_type = Input;

	static constexpr ParserType type = LiteralType;

	static constexpr Result<result_type> parse(Input input)
	{
		if (not input.starts_with(str.view()))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + str.size() }, { begin + str.size(), input.end() } };
		}
	}

	static constexpr Result<void> lookahead(Input input)
	{
		if (not input.starts_with(str.view()))
			return { failure, input };
		else
		{
			input.remove_prefix(str.size());
			return { success, input };
		}
	}
};

TOK3N_END_NAMESPACE()