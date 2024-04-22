#pragma once
#include <k3/tok3n/parsers/compound/_fwd.h>
#include <k3/tok3n/detail/filter.h>
#include <k3/tok3n/detail/filtered_sequence.h>
#include <k3/tok3n/detail/is_not_type.h>
#include <k3/tok3n/detail/unwrap_if_single.h>

namespace k3::tok3n {

namespace detail::executors
{

	struct VoidResultTag {};

	template <class ResultType, class ValueType>
	struct Sequence
	{
		using StoredResult = std::conditional_t<std::same_as<ResultType, void>, VoidResultTag, ResultType>;

		Input<ValueType> input;
		StoredResult full_result = {};

		template <Parser P, std::size_t I, bool unwrapped>
		constexpr bool execute()
		{
			if constexpr (I == -1)
				return execute_lookahead<P>();
			else
				return execute_element<P, I, unwrapped>();
		}

		template <Parser P>
		constexpr bool execute_lookahead()
		{
			auto result = P::lookahead(input);
			input = result.remaining();
			return result.has_value();
		}

		template <Parser P, std::size_t I, bool unwrapped>
		constexpr bool execute_element()
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				if constexpr (unwrapped)
					full_result = std::move(*result);
				else
					std::get<I>(full_result) = std::move(*result);
				return true;
			}
			else
				return false;
		}
	};

}

template <Parser... Ps>
requires SequenceConstructible<Ps...>
struct Sequence
{
	using value_type = typename detail::head<Ps...>::value_type;

	template <EqualityComparableWith<value_type> V>
	using _trait = detail::unwrap_if_single<detail::filter<detail::is_not_type<void>, std::tuple, typename Ps::template result_for<V>...>>;
	template <EqualityComparableWith<value_type> V>
	using result_for = typename _trait<V>::type;
	template <EqualityComparableWith<value_type> V>
	static constexpr bool _unwrapped = _trait<V>::unwrapped;

	static constexpr ParserFamily family = SequenceFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		// This might be a problem because it default initializes all members
		using Executor = detail::executors::Sequence<result_for<value_type>, value_type>;
		Executor executor{ .input = input };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... && executor.execute<Ps, Is, _unwrapped<value_type>>());
		}(detail::filtered_sequence<detail::is_not_type<void>, typename Ps::template result_for<value_type>...>{});

		if (not successful)
			return { failure, input };

		if constexpr (std::same_as<result_for<value_type>, void>)
			return { success, executor.input };
		else
			return { success, std::move(executor.full_result), executor.input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		using Executor = detail::executors::Sequence<void, value_type>;
		Executor executor{ .input = input };

		bool successful = (... && executor.execute<Ps, -1, _unwrapped<value_type>>());

		if (successful)
			return { success, executor.input };
		else
			return { failure, input };
	}
};

} // namespace k3::tok3n
