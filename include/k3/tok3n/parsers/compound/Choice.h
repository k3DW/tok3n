#pragma once
#include <k3/tok3n/parsers/compound/_fwd.h>
#include <k3/tok3n/detail/head.h>

namespace k3::tok3n {

namespace detail::executors
{

	template <class ResultType, class ValueType>
	struct Choice
	{
		Input<ValueType> input;
		Result<ResultType, ValueType>& result;

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
	using value_type = typename detail::head<Ps...>::value_type;
	using result_type = typename detail::head<Ps...>::result_type;

	static constexpr ParserFamily family = ChoiceFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input)
	{
		Result<result_type, V> result;

		using Executor = detail::executors::Choice<result_type, V>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		Result<void, V> result;

		using Executor = detail::executors::Choice<void, V>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}
};

} // namespace k3::tok3n
