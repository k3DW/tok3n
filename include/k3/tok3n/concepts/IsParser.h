#pragma once
#include <k3/tok3n/concepts/Parser.h>

namespace k3::tok3n {

namespace detail
{
	struct DoNotCareAboutResultTag {};
}

template <class P, ParserFamily family, class R = detail::DoNotCareAboutResultTag>
concept IsParser =
	Parser<P> and
	P::family == family and
	(std::same_as<R, detail::DoNotCareAboutResultTag> or std::same_as<typename P::result_type, R>);

} // namespace k3::tok3n
