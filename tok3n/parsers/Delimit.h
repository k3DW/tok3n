#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::tok3n
{

template <Parser P, Parser Delimiter>
struct Delimit
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr Result<result_type> parse(Input input)
	{
		result_type results;

		auto result = P::parse(input);
		if (not result)
			return { failure, input };

		while (result)
		{
			input = result.remaining();
			results.emplace_back(std::move(result.value()));

			Result<void> delimited = Delimiter::lookahead(input);
			if (!delimited)
				break;

			result = P::parse(delimited.remaining());
		}

		return { success, std::move(results), input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		Result<void> result = P::lookahead(input);
		if (not result)
			return { failure, input };

		while (result)
		{
			input = result.remaining();

			Result<void> delimited = Delimiter::lookahead(input);
			if (!delimited)
				break;

			result = P::lookahead(delimited.remaining());
		}

		return { success, input };
	}
};

}
