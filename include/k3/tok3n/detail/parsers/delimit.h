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

template <parser P, parser_compatible_with<P> D>
struct delimit_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename D::template result_for<V>>,
		std::conditional_t<
			std::same_as<void, typename P::template result_for<V>>,
			void,
			std::vector<typename P::template result_for<V>>
		>,
		std::conditional_t<
			std::same_as<void, typename P::template result_for<V>>,
			std::vector<typename D::template result_for<V>>,
			std::pair<std::vector<typename P::template result_for<V>>, std::vector<typename D::template result_for<V>>>
		>
	>;

	static constexpr parser_family family = delimit_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		result_builder<result_for<V>> builder;
		constexpr bool is_p_void = std::same_as<void, typename P::template result_for<V>>;
		constexpr bool is_d_void = std::same_as<void, typename D::template result_for<V>>;

		auto res = P::parse(input);
		if (not res.has_value())
			return result<result_for<V>, V>{ failure_tag, input };

		while (res.has_value())
		{
			input = res.remaining();
			if constexpr (not is_p_void)
			{
				if constexpr (is_d_void)
					builder.insert_back(std::move(res));
				else
					builder.insert_back_first(std::move(res));
			}

			auto delimit_res = D::parse(input);
			if (not delimit_res)
				break;

			res = P::parse(delimit_res.remaining());
			if constexpr (not is_d_void)
			{
				if (res.has_value())
				{
					if constexpr (is_p_void)
						builder.insert_back(std::move(delimit_res));
					else
						builder.insert_back_second(std::move(delimit_res));
				}
			}
		}

		return std::move(builder).build(input);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto res = P::lookahead(input);
		if (not res.has_value())
			return result<void, V>{ failure_tag, input };

		while (res.has_value())
		{
			input = res.remaining();

			auto delimit_result = D::lookahead(input);
			if (not delimit_result)
				break;

			res = P::lookahead(delimit_result.remaining());
		}

		return result<void, V>{ success_tag, input };
	}
};

} // namespace k3::tok3n::detail
