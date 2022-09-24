#pragma once
#include "util/meta.h"
#include "util/static_string.h"
#include <vector>
#include <optional>

namespace k3::tok3n
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
	Transform,
	Flatten,
	Ignore,
	Delimit,
	Custom,
};

template <class P> constexpr ParserType parser_type_v          = ParserType::None;
template <class P> constexpr ParserType parser_type_v<const P> = parser_type_v<P>;
template <class P> constexpr ParserType parser_type_v<P&>      = parser_type_v<P>;
template <class P> constexpr ParserType parser_type_v<P&&>     = parser_type_v<P>;

template <class P> concept IsOneChar    = parser_type_v<P> == ParserType::OneChar;
template <class P> concept IsNotChar    = parser_type_v<P> == ParserType::NotChar;
template <class P> concept IsLiteral    = parser_type_v<P> == ParserType::Literal;
template <class P> concept IsChoice     = parser_type_v<P> == ParserType::Choice;
template <class P> concept IsSequence   = parser_type_v<P> == ParserType::Sequence;
template <class P> concept IsOneOrMore  = parser_type_v<P> == ParserType::OneOrMore;
template <class P> concept IsZeroOrMore = parser_type_v<P> == ParserType::ZeroOrMore;
template <class P> concept IsZeroOrOne  = parser_type_v<P> == ParserType::ZeroOrOne;
template <class P> concept IsTransform  = parser_type_v<P> == ParserType::Transform;
template <class P> concept IsFlatten    = parser_type_v<P> == ParserType::Flatten;
template <class P> concept IsIgnore     = parser_type_v<P> == ParserType::Ignore;
template <class P> concept IsDelimit    = parser_type_v<P> == ParserType::Delimit;
template <class P> concept IsCustom     = parser_type_v<P> == ParserType::Custom;

using Input = std::string_view;

template <class T>
class Result;

template <class R, class T> constexpr bool is_result_v = false;
template <class R, class T> concept IsResult = is_result_v<R, T>;

template <class T> constexpr bool is_result_v<Result<T>, T> = true;

template <class P>
concept Parser =
	(parser_type_v<P> != ParserType::None) &&
	(std::is_empty_v<P>) &&
	requires { typename P::result_type; } &&
	requires (Input input)
	{
		{ P::parse(input) } -> IsResult<typename P::result_type>;
		{ P::lookahead(input) } -> IsResult<void>;
	};


template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii()) && (str.size() != 0)
struct OneChar;

template <static_string str>
constexpr ParserType parser_type_v<OneChar<str>> = ParserType::OneChar;


template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii()) && (str.size() != 0)
struct NotChar;

template <static_string str>
constexpr ParserType parser_type_v<NotChar<str>> = ParserType::NotChar;


template <static_string str>
requires (str.ascii()) && (str.size() != 0)
struct Literal;

template <static_string str>
constexpr ParserType parser_type_v<Literal<str>> = ParserType::Literal;


template <Parser... Ps>
requires (sizeof...(Ps) >= 2) && mp::all_same<typename Ps::result_type...>
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


template <Parser P, auto function>
requires requires { std::invoke(function, std::declval<typename P::result_type>()); }
struct Transform;

template <Parser P, auto function>
constexpr ParserType parser_type_v<Transform<P, function>> = ParserType::Transform;


template <auto function>
struct fn_t {};

template <auto function>
constexpr auto fn = fn_t<function>{};


template <class T> constexpr bool flattenable_v          = false;
template <class T> constexpr bool flattenable_v<const T> = flattenable_v<T>;
template <class T> constexpr bool flattenable_v<T&>      = flattenable_v<T>;
template <class T> constexpr bool flattenable_v<T&&>     = flattenable_v<T>;

template <> constexpr bool flattenable_v<std::string_view> = true;
template <class T> constexpr bool flattenable_v<std::vector<T>> = flattenable_v<T>;
template <class T> constexpr bool flattenable_v<std::optional<T>> = flattenable_v<T>;
template <class... Ts> constexpr bool flattenable_v<std::tuple<Ts...>> = (... && flattenable_v<Ts>);

template <class T> concept Flattenable = flattenable_v<T>;

template <Parser P>
requires Flattenable<typename P::result_type>
struct Flatten;

template <Parser P>
constexpr ParserType parser_type_v<Flatten<P>> = ParserType::Flatten;

constexpr struct flatten_t {} flatten;


template <Parser P>
struct Ignore;

template <Parser P>
constexpr ParserType parser_type_v<Ignore<P>> = ParserType::Ignore;


template <Parser P, Parser Delimiter>
struct Delimit;

template <Parser P, Parser Delimiter>
constexpr ParserType parser_type_v<Delimit<P, Delimiter>> = ParserType::Delimit;


struct CustomBase {};

template <class CRTP>
struct Custom : CustomBase
{
	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<typename P::result_type> parse(Input input)
	{
		return decltype(P::get_parser())::parse(input);
	}

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<void> lookahead(Input input)
	{
		return decltype(P::get_parser())::lookahead(input);
	}
};

template <std::derived_from<CustomBase> P>
constexpr ParserType parser_type_v<P> = ParserType::Custom;

}
