#pragma once
#include <k3/tok3n/parsers/compound/_fwd.h>
#include <k3/tok3n/detail/filter.h>
#include <k3/tok3n/detail/head.h>
#include <k3/tok3n/detail/is_not_type.h>
#include <k3/tok3n/detail/unwrap_if_single.h>
#include <variant>

namespace k3::tok3n {

namespace detail
{

	template <class ResultType, class ValueType>
	struct ChoiceExecutor : ExecutorData<ResultType>
	{
		Input<ValueType> input;

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
			if (not result.has_value())
				return false;

			input = result.remaining();
			if constexpr (not std::same_as<void, ResultType>)
			{
				if constexpr (not unwrapped)
					this->full_result.emplace<I>(std::move(*result));
				else if constexpr (std::is_move_assignable_v<ResultType>)
					this->full_result = std::move(*result);
				else
					this->full_result = *result;
			}
			return true;
		}
	};

} // namespace detail

template <Parser... Ps>
requires ChoiceConstructible<Ps...>
struct Choice
{
	using value_type = typename detail::head<Ps...>::value_type;

	template <EqualityComparableWith<value_type> V>
	using _filtered = detail::filter_deduplicate_with_index<detail::is_not_type<void>, typename Ps::template result_for<V>...>;

	template <EqualityComparableWith<value_type> V>
	using _trait = detail::unwrap_if_single<typename _filtered<V>::type>;
	template <EqualityComparableWith<value_type> V>
	using result_for = typename std::conditional_t<_trait<V>::unwrapped,
		_trait<V>,
		detail::change_list<typename _trait<V>::type, std::variant>
	>::type;

	static constexpr ParserFamily family = ChoiceFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		using Executor = detail::ChoiceExecutor<result_for<V>, V>;
		Executor executor{ .input = input };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... || executor.execute<Ps, Is, _trait<V>::unwrapped>());
		}(typename _filtered<V>::sequence{});

		if (not successful)
			return Result<result_for<V>, V>{ failure, input };

		if constexpr (std::same_as<result_for<V>, void>)
			return Result<result_for<V>, V>{ success, executor.input };
		else
			return Result<result_for<V>, V>{ success, std::move(executor.full_result), executor.input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		using Executor = detail::ChoiceExecutor<void, V>;
		Executor executor{ .input = input };

		bool successful = (... || executor.execute<Ps, static_cast<std::size_t>(-1), _trait<V>::unwrapped>());

		if (successful)
			return Result<void, V>{ success, executor.input };
		else
			return Result<void, V>{ failure, input };
	}
};

} // namespace k3::tok3n
