// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/optimizations/guaranteed_contiguous.h>

namespace k3::tok3n::detail {

template <guaranteed_contiguous P, guaranteed_contiguous... Ps>
struct join_parser<sequence_parser<P, Ps...>> : impl::join_parser_base<join_parser<sequence_parser<P, Ps...>>>
{
	friend struct impl::join_parser_base<join_parser<sequence_parser<P, Ps...>>>;
	using value_type = typename impl::join_parser_base<join_parser<sequence_parser<P, Ps...>>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;
        
		const input_span original_input = input;
		const auto* const ptr = input.data();
		std::size_t length = 0;

        const auto executor = [&]<parser Inner>(Inner) {
            Out nested;
            result<void, V> res = join_parser<Inner>::parse(input, nested);
            if (not res.has_value())
                return false;
            input = res.remaining();
            length += nested.size();
            return true;
        };

        const bool successful = (executor(P{}) and ... and executor(Ps{}));
		if (successful)
			out = Out{ ptr, length };
        return result<void, V>{ successful, successful ? input : original_input };
	}
};

} // namespace k3::tok3n::detail
