#pragma once
#include <tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE()

template <class P, ParserType type>
concept IsParser = Parser<P> and (P::type == type);

#define TOK3N_X_MACRO(TYPE)                           \
	template <class P>                                \
	concept Is##TYPE = IsParser<P, ParserType::TYPE>;
TOK3N_DO_FOR_ALL_PARSER_TYPES(TOK3N_X_MACRO)
#undef TOK3N_X_MACRO

TOK3N_END_NAMESPACE()
