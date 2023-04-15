#pragma once
#include <k3/tok3n/parsers/_constructible/repeat.h>
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <Parser P, Parser D>
requires constructible::Delimit<P, D>
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

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			result = P::parse(delimit_result.remaining());
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

			auto delimit_result = D::lookahead(input);
			if (not delimit_result)
				break;

			result = P::lookahead(delimit_result.remaining());
		}

		return { success, input };
	}
};

TOK3N_END_NAMESPACE()
