#pragma once
#include "util/pack_manip.h"
#include "util/static_string.h"

namespace k3::parser
{

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
	ZeroOrOne,
};

template <class P>
constexpr ParserType parser_type_v = ParserType::None;

template <class P> concept IsOneChar    = parser_type_v<P> == ParserType::OneChar;
template <class P> concept IsNotChar    = parser_type_v<P> == ParserType::NotChar;
template <class P> concept IsLiteral    = parser_type_v<P> == ParserType::Literal;
template <class P> concept IsChoice     = parser_type_v<P> == ParserType::Choice;
template <class P> concept IsSequence   = parser_type_v<P> == ParserType::Sequence;
template <class P> concept IsOneOrMore  = parser_type_v<P> == ParserType::OneOrMore;
template <class P> concept IsZeroOrMore = parser_type_v<P> == ParserType::ZeroOrMore;
template <class P> concept IsZeroOrOne  = parser_type_v<P> == ParserType::ZeroOrOne;

using Input = std::string_view;

template <class T>
class Result;

template <class R> constexpr bool is_result_v = false;
template <class R> concept IsResult = is_result_v<R>;

template <class T> constexpr bool is_result_v<Result<T>> = true;

template <class P>
concept Parser =
	(parser_type_v<P> != ParserType::None) &&
	(sizeof(P) == 1) &&
	requires (Input input)
	{
		{ P::parse(input) } -> IsResult;
	};


template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii())
struct OneChar;

template <static_string str>
constexpr ParserType parser_type_v<OneChar<str>> = ParserType::OneChar;


template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii())
struct NotChar;

template <static_string str>
constexpr ParserType parser_type_v<NotChar<str>> = ParserType::NotChar;


template <static_string str>
requires (str.ascii()) && (str.size() > 0)
struct Literal;

template <static_string str>
constexpr ParserType parser_type_v<Literal<str>> = ParserType::Literal;


template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Choice;

template <Parser... Ps>
constexpr ParserType parser_type_v<Choice<Ps...>> = ParserType::Choice;


template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Sequence;

template <Parser... Ps>
constexpr ParserType parser_type_v<Sequence<Ps...>> = ParserType::Sequence;


template <Parser P>
struct OneOrMore;

template <Parser P>
constexpr ParserType parser_type_v<OneOrMore<P>> = ParserType::OneOrMore;


template <Parser P>
struct ZeroOrMore;

template <Parser P>
constexpr ParserType parser_type_v<ZeroOrMore<P>> = ParserType::ZeroOrMore;


template <Parser P>
struct ZeroOrOne;

template <Parser P>
constexpr ParserType parser_type_v<ZeroOrOne<P>> = ParserType::ZeroOrOne;

}
