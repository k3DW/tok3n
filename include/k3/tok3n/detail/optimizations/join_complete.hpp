// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P>
struct join_parser<complete_parser<P>> : impl::join_parser_base<join_parser<complete_parser<P>>>
{
	friend struct impl::join_parser_base<join_parser<complete_parser<P>>>;
	using value_type = typename impl::join_parser_base<join_parser<complete_parser<P>>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
		const input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		result<void, V> res = join_parser<P>::parse(input, out);
		if (not res.has_value() or not res.remaining().empty())
			return { failure_tag, input };
		else
			return res;
	}
};

} // namespace k3::tok3n::detail
