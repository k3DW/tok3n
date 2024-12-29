// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <functional>
#include <utility>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
struct filter_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	requires std::convertible_to<
		invoke_result_ex_t<
			typename FunctionValue::value_type,
			std::add_lvalue_reference_t<std::add_const_t<typename P::template result_for<V>>> // If we just added `const&` here, it would fail for `void`
		>,
		bool
	>
	using result_for = typename P::template result_for<V>;

	static constexpr parser_family family = filter_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
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
	requires parsable_into<P, R&&, Out>
		and std::convertible_to<std::invoke_result_t<typename FunctionValue::value_type, const Out&>, bool>
	static constexpr auto parse(R&& r, Out& out)
	{
		return _parse_impl(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}

private:
	template <input_constructible_for<value_type> R, class... Out>
	requires (sizeof...(Out) <= 1)
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out&... out)
	{
		const input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		result<void, V> res = P::parse(input, out...);
		if (not res.has_value())
			return { failure_tag, input };
		
		static_assert(requires { { std::invoke(FunctionValue::value, std::as_const(out)...) } -> std::convertible_to<bool>; });
		if (std::invoke(FunctionValue::value, std::as_const(out)...))
			return res;
		else
			return { failure_tag, input };
	}
};

} // namespace k3::tok3n::detail
