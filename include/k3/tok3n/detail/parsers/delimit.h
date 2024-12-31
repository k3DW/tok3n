// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <utility>
#include <vector>

namespace k3::tok3n::detail {

namespace impl {

template <parser P, parser D, class CallP, class CallD>
struct delimit_executor
{
private:
	template <std::size_t I>
	requires (I <= 1)
	using parser_type = std::conditional_t<I == 0, P, D>;

	template <std::size_t I>
	requires (I <= 1)
	using call_type = std::conditional_t<I == 0, CallP, CallD>;

public:
	template <std::size_t I, class V>
	static constexpr auto call(input_span<V> in)
	{
		if constexpr (call_type<I>::kind == call_kind::parse_into)
		{
			typename parser_type<I>::template result_for<V> element;
			// TODO: Both of these lines cause a compile error on clang, even though they should be exactly the same
			// return call_type<I>{}(parser_type<I>{}, in, element)
			// return call_parse_into(parser_type<I>{}, in, element)
			return parser_type<I>::parse(in, element)
				.with_value(std::move(element));
		}
		else
		{
			return call_type<I>{}(parser_type<I>{}, in);
		}
	}

	template <std::size_t I, class T, class V>
	static constexpr void maybe_push([[maybe_unused]] result<T, V>&& res, [[maybe_unused]] auto&... out)
	{
		static_assert((call_type<I>::kind != call_kind::parse_into) == std::same_as<T, void>);
		if constexpr (call_type<I>::kind == call_kind::parse_into)
		{
			if constexpr (call_type<1-I>::kind == call_kind::parse_into)
				(..., (push(adl_get<I>(out), *std::move(res))));
			else
				(..., (push(out, *std::move(res))));
		}
	}
};

} // namespace impl

template <parser P, parser_compatible_with<P> D>
struct delimit_parser
{
	using value_type = typename P::value_type;

private:
	template <equality_comparable_with<value_type> V>
	using result_for_p = typename P::template result_for<V>;

	template <equality_comparable_with<value_type> V>
	using result_for_d = typename D::template result_for<V>;

public:
	template <equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, result_for_d<V>>,
		std::conditional_t<
			std::same_as<void, result_for_p<V>>,
			void,
			std::vector<result_for_p<V>>
		>,
		std::conditional_t<
			std::same_as<void, result_for_p<V>>,
			std::vector<result_for_d<V>>,
			std::pair<std::vector<result_for_p<V>>, std::vector<result_for_d<V>>>
		>
	>;

	static constexpr parser_family family = delimit_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		if constexpr (std::same_as<void, result_for<input_value_t<R>>>)
		{
			return _impl(call_parse, call_parse, std::forward<R>(r));
		}
		else
		{
			result_for<input_value_t<R>> out;
			return parse(std::forward<R>(r), out)
				.with_value(std::move(out));
		}
	}

	template <input_constructible_for<value_type> R, class Out>
	requires parsable_into<P, R&&, result_for_p<input_value_t<R>>>
		and parsable_into<D, R&&, result_for_d<input_value_t<R>>>
		and pushable<adl_get_t<Out, 0>, result_for_p<input_value_t<R>>&&>
		and pushable<adl_get_t<Out, 1>, result_for_d<input_value_t<R>>&&>
	static constexpr auto parse(R&& r, Out& out)
	{
		return _impl(call_parse_into, call_parse_into, std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R, class Out>
	requires std::same_as<void, result_for_p<input_value_t<R>>>
		and parsable_into<D, R&&, result_for_d<input_value_t<R>>>
		and pushable<Out, result_for_d<input_value_t<R>>&&>
	static constexpr auto parse(R&& r, Out& out)
	{
		return _impl(call_parse, call_parse_into, std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R, class Out>
	requires std::same_as<void, result_for_d<input_value_t<R>>>
		and parsable_into<P, R&&, result_for_p<input_value_t<R>>>
		and pushable<Out, result_for_p<input_value_t<R>>&&>
	static constexpr auto parse(R&& r, Out& out)
	{
		return _impl(call_parse_into, call_parse, std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return _impl(call_lookahead, call_lookahead, std::forward<R>(r));
	}

private:
	template <class CallP, class CallD, input_constructible_for<value_type> R, class... Out>
	requires (sizeof...(Out) <= 1)
	static constexpr result<void, input_value_t<R>> _impl(CallP, CallD, R&& r, Out&... out)
	{
		input_span input{ std::forward<R>(r) };

		constexpr auto executor = impl::delimit_executor<P, D, CallP, CallD>{};

		auto res = executor.template call<0>(input);
		if (not res.has_value())
			return { failure_tag, input };

		executor.template maybe_push<0>(std::move(res), out...);

		while (res.has_value())
		{
			input = res.remaining();

			auto delimit_res = executor.template call<1>(input);
			if (not delimit_res.has_value())
				break;

			res = executor.template call<0>(delimit_res.remaining());
			if (res.has_value())
			{
				executor.template maybe_push<0>(std::move(res), out...);
				executor.template maybe_push<1>(std::move(delimit_res), out...);
			}
		}

		return { success_tag, input };
	}
};

} // namespace k3::tok3n::detail
