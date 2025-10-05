// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_NAMED_HPP
#define K3_TOK3N_DETAIL_PARSERS_NAMED_HPP

#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <k3/tok3n/detail/static_array.hpp>

namespace k3::tok3n::detail {

template <parser P, static_array str>
struct named_parser
{
	using value_type = typename P::value_type;
	
	template <equality_comparable_with<value_type> V>
	using result_for = typename P::template result_for<V>;

	static constexpr parser_family family = named_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r) -> result<result_for<input_value_t<R>>, input_value_t<R>>
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
	static constexpr auto parse(R&& r, Out& out) -> result<void, input_value_t<R>>
	{
		return P::parse(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r) -> result<void, input_value_t<R>>
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_NAMED_HPP
