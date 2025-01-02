// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <class CRTP, class ValueType>
requires guaranteed_contiguous<custom_parser<CRTP, ValueType>>
struct join_parser<custom_parser<CRTP, ValueType>> : impl::join_parser_base<join_parser<custom_parser<CRTP, ValueType>>>
{
	friend struct impl::join_parser_base<join_parser<custom_parser<CRTP, ValueType>>>;
	using value_type = typename impl::join_parser_base<join_parser<custom_parser<CRTP, ValueType>>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
        return join_parser<decltype(CRTP::get_parser())>::parse(std::forward<R>(r), out);
	}
};

} // namespace k3::tok3n::detail
