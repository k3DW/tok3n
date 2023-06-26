#pragma once
#include <k3/tok3n/parsers/compound/_fwd.h>
#include <k3/tok3n/detail/head.h>

namespace k3::tok3n {

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
requires ChoiceConstructible<Ps...>
struct Choice
{
	using result_type = typename detail::head<Ps...>::result_type;

	static constexpr ParserType type = ChoiceType;

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

} // namespace k3::tok3n
