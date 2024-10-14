// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <optional>

namespace k3::tok3n::detail {

template <parser P>
struct maybe_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::optional<typename P::template result_for<V>>
	>;

	static constexpr parser_family family = maybe_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		result_builder<result_for<V>> builder;

		auto res = P::parse(input);
		if (res.has_value())
			builder.emplace(std::move(res));

		return std::move(builder).build(res.remaining());
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto res = P::lookahead(input);
		if (res.has_value())
			return result<void, V>{ success_tag, res.remaining() };
		else
			return result<void, V>{ success_tag, input };
	}
};

} // namespace k3::tok3n::detail
