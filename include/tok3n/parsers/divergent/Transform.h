#pragma once
#include "tok3n/parsers/Details.h"
#include "tok3n/types.h"
#include "tok3n/concepts.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, auto function>
requires detail::Transform_able<P, function>
struct Transform
{
	using result_type = detail::Transform_result<P, function>;

	static constexpr ParserType type = ParserType::Transform;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::invoke(function, std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
