// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/filter.h>
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <variant>

namespace k3::tok3n::detail {

template <parser P, parser_compatible_with<P>... Ps>
struct choice_parser
{
	using value_type = typename P::value_type;

private:
	template <equality_comparable_with<value_type> V>
	using _trait = compound_trait<filter_out_void_deduplicate, std::variant, V, P, Ps...>;

public:
	template <equality_comparable_with<value_type> V>
	using result_for = typename _trait<V>::result_for;

	static constexpr parser_family family = choice_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Executor = impl::choice_executor<result_for<V>, V, _trait<V>::unwrapped>;
		Executor executor{ input };

		bool successful = [&executor]<std::size_t I, std::size_t... Is>(std::index_sequence<I, Is...>)
		{
			return (executor.template execute<P, I>() or ... or executor.template execute<Ps, Is>());
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

		using Executor = impl::choice_executor<void, V, _trait<V>::unwrapped>;
		Executor executor{ input };

		bool successful = (executor.template execute<P>() or ... or executor.template execute<Ps>());

		if (successful)
			return result<void, V>{ success_tag, executor.input };
		else
			return result<void, V>{ failure_tag, input };
	}
};

} // namespace k3::tok3n::detail
