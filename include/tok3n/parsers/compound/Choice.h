#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/types/Result.h"

TOK3N_BEGIN_NAMESPACE()

namespace detail::executors
{

	template <class ResultType>
	struct Choice
	{
		Input input;
		Result<ResultType>& result;

		template <Parser P>
		constexpr bool execute()
		{
			if constexpr (std::is_same_v<ResultType, void>)
				result = P::lookahead(input);
			else
				result = P::parse(input);
			return result.has_value();
		}
	};

}

template <Parser... Ps>
requires detail::Choice_able<Ps...>
struct Choice
{
	using result_type = detail::Choice_result<Ps...>;

	static constexpr ParserType type = ParserType::Choice;

	static constexpr Result<result_type> parse(Input input)
	{
		Result<result_type> result;

		using Executor = detail::executors::Choice<result_type>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}

	static constexpr Result<void> lookahead(Input input)
	{
		Result<void> result;

		using Executor = detail::executors::Choice<void>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}
};

TOK3N_END_NAMESPACE()
