// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P, guaranteed_contiguous... Ps>
struct join_parser<choice_parser<P, Ps...>> : impl::join_parser_base<join_parser<choice_parser<P, Ps...>>>
{
	friend struct impl::join_parser_base<join_parser<choice_parser<P, Ps...>>>;
	using value_type = typename impl::join_parser_base<join_parser<choice_parser<P, Ps...>>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

        const auto executor = [&]<parser Inner>(Inner) {
            result<void, V> res = join_parser<Inner>::parse(input, out);
            input = res.remaining();
            return res.has_value();
        };
        const bool successful = (executor(P{}) or ... or executor(Ps{}));
        return result<void, V>{ successful, input };
	}
};

} // namespace k3::tok3n::detail
