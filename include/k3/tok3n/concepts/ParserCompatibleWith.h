#pragma once
#include <k3/tok3n/concepts/Parser.h>

namespace k3::tok3n {

template <class P1, class P2>
concept ParserCompatibleWith = 
	Parser<P1> and
	Parser<P2> and
	std::same_as<typename P1::value_type, typename P2::value_type>;

} // namespace k3::tok3n
