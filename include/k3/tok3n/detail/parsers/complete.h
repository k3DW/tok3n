// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n::detail {

template <parser P>
struct complete_parser
{
	using value_type = typename P::value_type;
	
	template <equality_comparable_with<value_type> V>
	using result_for = typename P::template result_for<V>;

	static constexpr parser_family family = complete_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto res = P::parse(input);
		if (not res.has_value() or not res.remaining().empty())
			return result<result_for<V>, V>{ failure_tag, input };
		else
			return res;
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto res = P::lookahead(input);
		if (not res.has_value() or not res.remaining().empty())
			return result<void, V>{ failure_tag, input };
		else
			return res;
	}
};

} // namespace k3::tok3n::detail
