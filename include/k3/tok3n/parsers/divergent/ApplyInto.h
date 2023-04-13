#pragma once
#include <tok3n/parsers/_constructible/divergent.h>
#include <tok3n/types.h>
#include <tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <Parser P, class T>
requires constructible::ApplyInto<P, T>
struct ApplyInto
{
	using result_type = T;

	static constexpr ParserType type = ApplyIntoType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::make_from_tuple<result_type>(std::move(*result)), result.remaining()};
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
