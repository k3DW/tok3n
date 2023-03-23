#pragma once
#include <tok3n/utilities/namespace.h>

TOK3N_BEGIN_NAMESPACE()

enum class ParserType
{
	None,
	OneChar,
	NotChar,
	Literal,
	Choice,
	Sequence,
	OneOrMore,
	ZeroOrMore,
	Maybe,
	Exactly,
	Ignore,
	Transform,
	ApplyTransform,
	Join,
	Delimit,
	Into,
	ApplyInto,
	Constant,
	Defaulted,
	Complete,
	Custom,
};

template <class P> constexpr ParserType parser_type_v          = ParserType::None;
template <class P> constexpr ParserType parser_type_v<const P> = parser_type_v<P>;
template <class P> constexpr ParserType parser_type_v<P&>      = parser_type_v<P>;
template <class P> constexpr ParserType parser_type_v<P&&>     = parser_type_v<P>;

TOK3N_END_NAMESPACE()
