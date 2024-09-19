#pragma once
#include <k3/tok3n/detail/parsers/basic_base.h>
#include <k3/tok3n/detail/parsers/join.h>
#include <k3/tok3n/detail/parsers/maybe.h>

namespace k3::tok3n::detail {

template <template <static_array> class Basic, static_array arr>
struct join_parser<maybe_parser<Basic<arr>>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <equality_comparable_with<value_type> V>
	using result_for = output_span<V>;

	static constexpr parser_family family = join_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Traits = impl::basic_parser_traits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return result<result_for<V>, V>{ success_tag, { input.data(), 0 }, input };

		return result<result_for<V>, V>{ success_tag, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}
	
	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Traits = impl::basic_parser_traits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return result<void, V>{ success_tag, input };

		return result<void, V>{ success_tag, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n::detail
