#pragma once
#include <k3/tok3n.h>

#include "traits.h"
#include "framework/assert.h"
#include "framework/comparison.h"
#include "framework/parse.h"
#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/compound.h"
#include "samples/divergent.h"
#include "samples/functions.h"
#include "samples/repeat.h"

TOK3N_BEGIN_NAMESPACE(tests)

constexpr auto the_parser_list = adaptor_list + basic_list + compound_list + divergent_list + repeat_list;

#define TOK3N_ASSERT_P(condition, message) \
	do {                                   \
		if constexpr (not (condition))     \
			typename P::__error_with_type; \
	} while(false)


struct underlying
{
private:
	template <template <class> class ParserTemplate, Parser P>
	static consteval auto impl(ParserTemplate<P>) { return P{}; }

	template <template <StaticString> class ParserTemplate, StaticString str>
	static consteval auto impl(ParserTemplate<str>) { return str; }

public:
	template <Parser P>
	using parser = decltype(impl(P{}));

	template <Parser P>
	static constexpr auto string = impl(P{});
};

consteval bool check_all_samples(auto checker)
{
	return [checker]<Parser... Ps>(parser_list<Ps...>) -> bool
	{
		return (... && checker(Ps{}));
	}(the_parser_list);
}

TOK3N_END_NAMESPACE(tests)
