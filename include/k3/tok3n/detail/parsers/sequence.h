#pragma once
#include <k3/tok3n/detail/filter.h>
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <tuple>

namespace k3::tok3n::detail {

namespace impl {

template <class ResultType, class ValueType, bool unwrapped>
struct sequence_executor : empty_if_void<ResultType>
{
	input_span<ValueType> input;

	template <parser P, std::size_t I = static_cast<std::size_t>(-1)>
	constexpr bool execute()
	{
		if constexpr (I == static_cast<std::size_t>(-1))
			return execute_lookahead<P>();
		else
			return execute_element<P, I>();
	}

private:
	template <parser P>
	constexpr bool execute_lookahead()
	{
		auto res = P::lookahead(input);
		input = res.remaining();
		return res.has_value();
	}

	template <parser P, std::size_t I>
	constexpr bool execute_element()
	{
		auto res = P::parse(input);
		if (not res.has_value())
			return false;

		input = res.remaining();
		if constexpr (not std::same_as<void, ResultType>)
		{
			if constexpr (not unwrapped)
				std::get<I>(this->value) = std::move(*res);
			else
				this->value = std::move(*res);
		}
		return true;
	}
};

} // namespace impl

template <parser P, parser... Ps>
requires (... and std::same_as<typename P::value_type, typename Ps::value_type>)
struct sequence_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using _filtered = filter_out_void<typename P::template result_for<V>, typename Ps::template result_for<V>...>;

	template <equality_comparable_with<value_type> V>
	using _trait = unwrap_if_single<typename _filtered<V>::type>;
	template <equality_comparable_with<value_type> V>
	using result_for = typename std::conditional_t<_trait<V>::unwrapped,
		_trait<V>,
		change_list<typename _trait<V>::type, std::tuple>
	>::type;

	static constexpr parser_family family = sequence_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		// This might be a problem because it default initializes all members
		using Executor = impl::sequence_executor<result_for<V>, V, _trait<V>::unwrapped>;
		Executor executor{ .input = input };

		bool successful = [&executor]<std::size_t I, std::size_t... Is>(std::index_sequence<I, Is...>)
		{
			return (executor.template execute<P, I>() and ... and executor.template execute<Ps, Is>());
		}(typename _filtered<V>::sequence{});

		if (not successful)
			return result<result_for<V>, V>{ failure_tag, input };

		if constexpr (std::same_as<result_for<V>, void>)
			return result<result_for<V>, V>{ success_tag, executor.input };
		else
			return result<result_for<V>, V>{ success_tag, std::move(executor.value), executor.input };
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Executor = impl::sequence_executor<void, V, _trait<V>::unwrapped>;
		Executor executor{ .input = input };

		bool successful = (executor.template execute<P>() and ... and executor.template execute<Ps>());

		if (successful)
			return result<void, V>{ success_tag, executor.input };
		else
			return result<void, V>{ failure_tag, input };
	}
};

} // namespace k3::tok3n::detail
