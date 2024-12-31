// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parsers/join.h>
#include <k3/tok3n/detail/parsers/all_of.h>
#include <k3/tok3n/detail/parsers/any_of.h>
#include <k3/tok3n/detail/parsers/anything.h>
#include <k3/tok3n/detail/parsers/none_of.h>

namespace k3::tok3n::detail {

// template <template <static_array> class Basic, static_array arr>
template <parser Basic>
requires std::derived_from<Basic, impl::basic_parser_base<Basic>>
struct join_parser<Basic> : impl::join_parser_base<join_parser<Basic>>
{
	friend struct impl::join_parser_base<join_parser<Basic>>;
	using value_type = typename impl::join_parser_base<join_parser<Basic>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
        return Basic::parse(std::forward<R>(r), out);
	}
};

} // namespace k3::tok3n::detail
