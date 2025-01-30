// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_MAP_HPP
#define K3_TOK3N_DETAIL_PARSERS_MAP_HPP

#include <k3/tok3n/detail/helpers.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <functional>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
struct map_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = invoke_result_ex_t<
		typename FunctionValue::value_type,
		std::add_rvalue_reference_t<typename P::template result_for<V>> // If we just added `&&` here, it would fail for `void`
	>;

	static constexpr parser_family family = map_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r) -> result<result_for<input_value_t<R>>, input_value_t<R>>
	{
		if constexpr (std::same_as<void, result_for<input_value_t<R>>>)
		{
			return _parse_impl(std::forward<R>(r));
		}
		else
		{
			result_for<input_value_t<R>> out;
			return _parse_impl(std::forward<R>(r), out)
				.with_value(std::move(out));
		}
	}

	template <input_constructible_for<value_type> R, class Out>
	requires parsable_void<P, R&&>
		and invoke_assignable_to<Out&, typename FunctionValue::value_type>
	static constexpr auto parse(R&& r, Out& out) -> result<void, input_value_t<R>>
	{
		return _parse_impl(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R, class Out>
	requires parsable_into<P, R&&, typename P::template result_for<input_value_t<R>>>
		and invoke_assignable_to<Out&, typename FunctionValue::value_type, typename P::template result_for<input_value_t<R>>&&>
	static constexpr auto parse(R&& r, Out& out) -> result<void, input_value_t<R>>
	{
		return _parse_impl(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r) -> result<void, input_value_t<R>>
	{
		return P::lookahead(std::forward<R>(r));
	}

private:
	template <input_constructible_for<value_type> R, class... Out>
	requires (sizeof...(Out) <= 1)
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out&... out)
	{
		using V = input_value_t<R>;

		if constexpr (std::same_as<void, typename P::template result_for<V>>)
		{
			result<void, V> res = P::parse(std::forward<R>(r));
			if (not res.has_value())
				return { failure_tag, res.remaining() };

			if constexpr (sizeof...(out) == 0)
				std::invoke(FunctionValue::value);
			else
				(..., (out = std::invoke(FunctionValue::value)));
			return { success_tag, res.remaining() };
		}
		else
		{
			typename P::template result_for<V> before;
			result<void, V> res = P::parse(std::forward<R>(r), before);
			if (not res.has_value())
				return { failure_tag, res.remaining() };

			if constexpr (sizeof...(out) == 0)
				std::invoke(FunctionValue::value, std::move(before));
			else
				(..., (out = std::invoke(FunctionValue::value, std::move(before))));
			return { success_tag, res.remaining() };
		}
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_MAP_HPP
