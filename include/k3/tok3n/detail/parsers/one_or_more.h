// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <vector>

namespace k3::tok3n::detail {

template <parser P>
struct one_or_more_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::vector<typename P::template result_for<V>>
	>;

	static constexpr parser_family family = one_or_more_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		result_builder<result_for<V>> builder;
		bool successful = false;

		while (true)
		{
			auto res = P::parse(input);
			input = res.remaining();
			successful |= res.has_value();
			if (not res.has_value())
				break;
			builder.insert_back(std::move(res));
		}

		if (successful)
			return std::move(builder).build(input);
		else
			return result<result_for<V>, V>{ failure_tag, input };
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		bool successful = false;

		while (true)
		{
			auto res = P::lookahead(input);
			input = res.remaining();
			successful |= res.has_value();
			if (not res.has_value())
				break;
		}

		if (successful)
			return result<void, V>{ success_tag, input };
		else
			return result<void, V>{ failure_tag, input };
	}
};

} // namespace k3::tok3n::detail
