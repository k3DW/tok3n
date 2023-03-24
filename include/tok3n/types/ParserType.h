#pragma once
#include <tok3n/namespace.h>

#define TOK3N_DO_FOR_ALL_PARSER_TYPES(XX) \
	XX(OneChar)                           \
	XX(NotChar)                           \
	XX(Literal)                           \
	XX(Choice)                            \
	XX(Sequence)                          \
	XX(OneOrMore)                         \
	XX(ZeroOrMore)                        \
	XX(Maybe)                             \
	XX(Exactly)                           \
	XX(Ignore)                            \
	XX(Transform)                         \
	XX(ApplyTransform)                    \
	XX(Join)                              \
	XX(Delimit)                           \
	XX(Into)                              \
	XX(ApplyInto)                         \
	XX(Constant)                          \
	XX(Defaulted)                         \
	XX(Complete)                          \
	XX(Custom)

TOK3N_BEGIN_NAMESPACE()

enum class ParserType
{
	None,

#define TOK3N_X_MACRO(TYPE) \
	TYPE,
TOK3N_DO_FOR_ALL_PARSER_TYPES(TOK3N_X_MACRO)
#undef TOK3N_X_MACRO

	END
};

TOK3N_END_NAMESPACE()
