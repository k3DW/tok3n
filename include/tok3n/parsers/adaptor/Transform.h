#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, auto function>
requires requires { std::invoke(function, std::declval<typename P::result_type>()); }
struct Transform
{
	using result_type = decltype(std::invoke(function, std::declval<typename P::result_type>()));

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::invoke(function, result.value()), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
