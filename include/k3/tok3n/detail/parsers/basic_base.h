// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n::detail {

namespace impl {

template <class P>
struct basic_parser_traits
{
	// using value_type;
	// static constexpr std::size_t length;
	// static constexpr bool failure_condition(input_span<value_type>);
};

template <class P>
struct basic_parser_base
{
	using value_type = typename basic_parser_traits<P>::value_type;
	
	template <equality_comparable_with<value_type> V>
    using result_for = output_span<V>;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		result_for<input_value_t<R>> out;
		return _impl(std::forward<R>(r), out)
			.with_value(std::move(out));
	}

	template <input_constructible_for<value_type> R, span_like Out>
	requires std::same_as<input_value_t<R>, typename Out::value_type>
	static constexpr auto parse(R&& r, Out& out)
	{
		return _impl(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return _impl(std::forward<R>(r));
	}

private:
	template <input_constructible_for<value_type> R, class... Out>
	requires (sizeof...(Out) <= 1)
	static constexpr result<void, input_value_t<R>> _impl(R&& r, Out&... out)
	{
		const input_span input{ std::forward<R>(r) };

		using Traits = basic_parser_traits<P>;
		if (Traits::failure_condition(input))
		{
			return { failure_tag, input };
		}
		else
		{
			(..., (out = Out{ input.data(), Traits::length }));
			return { success_tag, { input.data() + Traits::length, input.size() - Traits::length } };
		}
	}
};

} // namespace impl

} // namespace k3::tok3n::detail
