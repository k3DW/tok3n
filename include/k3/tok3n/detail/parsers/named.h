// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n::detail {

template <parser P, static_array str>
struct named_parser
{
	using value_type = typename P::value_type;
	
	template <equality_comparable_with<value_type> V>
	using result_for = typename P::template result_for<V>;

	static constexpr parser_family family = named_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		if constexpr (std::same_as<void, result_for<input_value_t<R>>>)
		{
			return P::parse(std::forward<R>(r));
		}
		else
		{
			result_for<input_value_t<R>> out;
			return P::parse(std::forward<R>(r), out)
				.with_value(std::move(out));
		}
	}

	template <input_constructible_for<value_type> R, class Out>
	requires parsable_into<P, R&&, Out>
	static constexpr auto parse(R&& r, Out& out)
	{
		return P::parse(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail
