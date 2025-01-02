// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_ONE_OR_MORE_HPP
#define K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_ONE_OR_MORE_HPP

#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P>
struct join_parser<one_or_more_parser<P>> : impl::join_parser_base<join_parser<one_or_more_parser<P>>>
{
	friend struct impl::join_parser_base<join_parser<one_or_more_parser<P>>>;
	using value_type = typename impl::join_parser_base<join_parser<one_or_more_parser<P>>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		const auto* const ptr = input.data();
		std::size_t length = 0;

		bool successful = false;
		while (true)
		{
			Out nested;
			result<void, V> res = join_parser<P>::parse(input, nested);
			successful |= res.has_value();
			if (not res.has_value())
				break;
			input = res.remaining();
			length += nested.size();
		}

		if (successful)
			out = Out{ ptr, length };
		return result<void, V>{ successful, input };
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPTIMIZATIONS_JOIN_ONE_OR_MORE_HPP
