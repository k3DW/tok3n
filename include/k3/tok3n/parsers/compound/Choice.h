#pragma once
#include <k3/tok3n/parsers/compound/_fwd.h>
#include <k3/tok3n/detail/head.h>

namespace k3::tok3n {

namespace detail::executors
{

	template <class ResultType>
	struct Choice
	{
		Input<char> input;
		Result<ResultType, char>& result;

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

	static constexpr ParserFamily type = ChoiceType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		Result<result_type, char> result;

		using Executor = detail::executors::Choice<result_type>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		Result<void, char> result;

		using Executor = detail::executors::Choice<void>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}
};

} // namespace k3::tok3n
