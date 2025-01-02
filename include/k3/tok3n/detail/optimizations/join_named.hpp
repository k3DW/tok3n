// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P, static_array str>
struct join_parser<named_parser<P, str>> : impl::join_parser_base<join_parser<named_parser<P, str>>>
{
	friend struct impl::join_parser_base<join_parser<named_parser<P, str>>>;
	using value_type = typename impl::join_parser_base<join_parser<named_parser<P, str>>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
		return join_parser<P>::parse(std::forward<R>(r), out);
	}
};

} // namespace k3::tok3n::detail
