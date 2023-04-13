#pragma once
#include <k3/tok3n/parsers/_constructible/basic.h>
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <StaticString str>
requires constructible::NotChar<str>
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

TOK3N_END_NAMESPACE()
