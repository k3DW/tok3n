#pragma once
#include "tok3n/parsers/Details.h"
#include "tok3n/types.h"
#include "tok3n/concepts.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, Parser Delimiter>
requires detail::Delimit_able<P, Delimiter>
struct Delimit
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr ParserType type = DelimitType;

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
