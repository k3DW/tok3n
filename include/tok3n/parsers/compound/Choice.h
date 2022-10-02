#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

namespace detail::executors
{

	template <class result_type>
	struct Choice
	{
		Input input;
		Result<result_type> result = {};

		template <Parser P>
		constexpr bool execute()
		{
			if constexpr (std::is_same_v<result_type, void>)
				result = P::lookahead(input);
			else
				result = P::parse(input);
			return result.has_value();
		}
	};

}

template <Parser... Ps>
requires (sizeof...(Ps) >= 2) && mp::all_same<typename Ps::result_type...>
struct Choice
{
	using result_type = typename mp::head<Ps...>::result_type;

	static constexpr Result<result_type> parse(Input input)
	{
		using Executor = detail::executors::Choice<result_type>;
		Executor executor{.input = input };
		(... || executor.execute<Ps>());

		return executor.result;
	}

	static constexpr Result<void> lookahead(Input input)
	{
		using Executor = detail::executors::Choice<void>;
		Executor executor{ .input = input };
		(... || executor.execute<Ps>());

		return executor.result;
	}
};

TOK3N_END_NAMESPACE()
