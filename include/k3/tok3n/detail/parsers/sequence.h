#pragma once
#include <k3/tok3n/detail/filter.h>
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <tuple>

namespace k3::tok3n::detail {

template <parser P, parser_compatible_with<P>... Ps>
struct sequence_parser
{
	using value_type = typename P::value_type;

private:
	template <equality_comparable_with<value_type> V>
	using _trait = compound_trait<filter_out_void, std::tuple, V, P, Ps...>;

public:
	template <equality_comparable_with<value_type> V>
	using result_for = typename _trait<V>::result_for;

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
		}(typename _trait<V>::sequence{});

		if (not successful)
			return result<result_for<V>, V>{ failure_tag, input };

		if constexpr (std::same_as<result_for<V>, void>)
			return result<result_for<V>, V>{ success_tag, executor.input };
		else
			return std::move(executor.builder).build(executor.input);
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
