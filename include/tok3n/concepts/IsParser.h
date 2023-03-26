#pragma once
#include <tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE()

template <class P, ParserType type>
concept IsParser = Parser<P> and (P::type == type);

TOK3N_END_NAMESPACE()
