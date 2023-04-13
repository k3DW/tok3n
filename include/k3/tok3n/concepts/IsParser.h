#pragma once
#include <tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE()

namespace detail
{
	struct DoNotCareAboutResultTag {};
}

template <class P, ParserType type, class R = detail::DoNotCareAboutResultTag>
concept IsParser =
	Parser<P> and
	P::type == type and
	(std::same_as<R, detail::DoNotCareAboutResultTag> or std::same_as<typename P::result_type, R>);

TOK3N_END_NAMESPACE()
