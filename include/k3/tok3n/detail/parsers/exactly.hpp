// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_EXACTLY_HPP
#define K3_TOK3N_DETAIL_PARSERS_EXACTLY_HPP

#include <k3/tok3n/detail/helpers.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <array>

namespace k3::tok3n::detail {

template <parser P, integral_constant_of<std::size_t> N>
requires (N::value != 0)
struct exactly_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::array<typename P::template result_for<V>, N::value>
	>;

	static constexpr parser_family family = exactly_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r) -> result<result_for<input_value_t<R>>, input_value_t<R>>
	{
		if constexpr (std::same_as<void, result_for<input_value_t<R>>>)
		{
			return _impl(call_parse, std::forward<R>(r));
		}
		else
		{
			result_for<input_value_t<R>> out;
			return _impl(call_parse_into, std::forward<R>(r), out)
				.with_value(std::move(out));
		}
	}

	template <input_constructible_for<value_type> R, indexable Out>
	requires parsable_into<P, R&&, std::remove_cvref_t<decltype(index(std::declval<Out&>(), std::size_t{}))>>
		and std::is_default_constructible_v<Out>
		and std::is_move_assignable_v<Out>
	static constexpr auto parse(R&& r, Out& out) -> result<void, input_value_t<R>>
	{
		return _impl(call_parse_into, std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r) -> result<void, input_value_t<R>>
	{
		return _impl(call_lookahead, std::forward<R>(r));
	}

private:
	template <class Call, input_constructible_for<value_type> R, class... Out>
	requires (sizeof...(Out) <= 1)
	static constexpr result<void, input_value_t<R>> _impl(Call call, R&& r, Out&... out)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		const input_span original_input = input;

		for (std::size_t i = 0; i < N::value; ++i)
		{
			result<void, V> res = call(P{}, input, index(out, i)...);
			if (not res.has_value())
			{
				(..., (out = Out{}));
				return result<void, V>{ failure_tag, original_input };
			}
			input = res.remaining();
		}
		return result<void, V>{ success_tag, input };
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_EXACTLY_HPP
