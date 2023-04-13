#pragma once
#include <k3/tok3n/namespace.h>

#define TOK3N_DO_FOR_ALL_PARSER_TYPES(XX) \
	XX(OneChar)                           \
	XX(NotChar)                           \
	XX(Literal)                           \
	XX(Choice)                            \
	XX(Sequence)                          \
	XX(Maybe)                             \
	XX(Exactly)                           \
	XX(OneOrMore)                         \
	XX(ZeroOrMore)                        \
	XX(Delimit)                           \
	XX(Ignore)                            \
	XX(Complete)                          \
	XX(Join)                              \
	XX(Transform)                         \
	XX(ApplyTransform)                    \
	XX(Into)                              \
	XX(ApplyInto)                         \
	XX(Constant)                          \
	XX(Defaulted)                         \
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

#define TOK3N_X_MACRO(TYPE) \
	constexpr ParserType TYPE##Type = ParserType::TYPE;
TOK3N_DO_FOR_ALL_PARSER_TYPES(TOK3N_X_MACRO)
#undef TOK3N_X_MACRO

TOK3N_END_NAMESPACE()
