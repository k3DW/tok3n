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

	template <EqualityComparableWith<value_type> V>
	using result_for = typename detail::head<Ps...>::template result_for<V>;

	static constexpr ParserFamily family = ChoiceFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		Result<result_for<value_type>, value_type> result;

		using Executor = detail::executors::Choice<result_for<value_type>, value_type>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		Result<void, value_type> result;

		using Executor = detail::executors::Choice<void, value_type>;
		Executor executor{ input, result };
		(... || executor.execute<Ps>());

		return result;
	}
};

} // namespace k3::tok3n
