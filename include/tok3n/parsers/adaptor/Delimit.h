#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, Parser Delimiter>
struct Delimit
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr Result<result_type> parse(Input input)
	{
		result_type results;

		auto result = P::parse(input);
		if (not result.has_value())
			return { failure, input };

		while (result)
		{
			input = result.remaining();
			results.emplace_back(std::move(*result));

			auto delimited = Delimiter::lookahead(input);
			if (not delimited.has_value())
				break;

			result = P::parse(delimited.remaining());
		}

		return { success, std::move(results), input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		auto result = P::lookahead(input);
		if (not result.has_value())
			return { failure, input };

		while (result)
		{
			input = result.remaining();

			auto delimited = Delimiter::lookahead(input);
			if (not delimited.has_value())
				break;

			result = P::lookahead(delimited.remaining());
		}

		return { success, input };
	}
};

TOK3N_END_NAMESPACE()
