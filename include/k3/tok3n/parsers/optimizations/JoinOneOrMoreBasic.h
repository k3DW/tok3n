#pragma once
#include <k3/tok3n/detail/parsers/basic_base.h>
#include <k3/tok3n/parsers/divergent/Join.h>
#include <k3/tok3n/parsers/repeat/OneOrMore.h>

namespace k3::tok3n {

template <template <detail::static_array> class Basic, detail::static_array arr>
struct Join<OneOrMore<Basic<arr>>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <detail::equality_comparable_with<value_type> V>
	using result_for = detail::output_span<V>;

	static constexpr detail::parser_family family = detail::join_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using Traits = detail::impl::basic_parser_traits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return detail::result<result_for<V>, V>{ detail::failure_tag, input };

		detail::output_span<V> res = { input.data(), Traits::length };
		input = input.subspan(Traits::length);

		while (not Traits::failure_condition(input))
		{
			res = { res.data(), res.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return detail::result<result_for<V>, V>{ detail::success_tag, res, input };
	}
	
	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using Traits = detail::impl::basic_parser_traits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return detail::result<void, V>{ detail::failure_tag, input };

		input = input.subspan(Traits::length);

		while (not Traits::failure_condition(input))
		{
			input = input.subspan(Traits::length);
		}

		return detail::result<void, V>{ detail::success_tag, input };
	}
};

} // namespace k3::tok3n
