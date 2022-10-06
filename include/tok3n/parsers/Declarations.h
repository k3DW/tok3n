#pragma once
#include "tok3n/utilities/meta.h"
#include "tok3n/utilities/static_string.h"
#include <vector>
#include <optional>
#include <utility>

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
	Transform,
	Join,
	Ignore,
	Delimit,
	Custom,
};

template <class P> constexpr ParserType parser_type_v          = ParserType::None;
template <class P> constexpr ParserType parser_type_v<const P> = parser_type_v<P>;
template <class P> constexpr ParserType parser_type_v<P&>      = parser_type_v<P>;
template <class P> constexpr ParserType parser_type_v<P&&>     = parser_type_v<P>;



namespace detail
{

	template <class Type, class With> constexpr bool is_joinable_v                   = std::is_same_v<Type, With>;
	template <class Type, class With> constexpr bool is_joinable_v<Type, const With> = is_joinable_v<Type, With>;
	template <class Type, class With> constexpr bool is_joinable_v<Type, With&>      = is_joinable_v<Type, With>;
	template <class Type, class With> constexpr bool is_joinable_v<Type, With&&>     = is_joinable_v<Type, With>;

	template <class Type, class Element>     constexpr bool is_joinable_v<Type, std::vector<Element>>    = is_joinable_v<Type, Element>;
	template <class Type, class Element>     constexpr bool is_joinable_v<Type, std::optional<Element>>  = is_joinable_v<Type, Element>;
	template <class Type, class... Elements> constexpr bool is_joinable_v<Type, std::tuple<Elements...>> = (... && is_joinable_v<Type, Elements>);

}



using Input = std::string_view;

template <class With>
concept Joinable = detail::is_joinable_v<Input, With>;

template <class T>
class Result;

template <class R, class T> constexpr bool is_result_v = false;
template <class T>          constexpr bool is_result_v<Result<T>, T> = true;

template <class R, class T> concept IsResult = is_result_v<R, T>;

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



template <class P> concept IsOneChar    = Parser<P> && parser_type_v<P> == ParserType::OneChar;
template <class P> concept IsNotChar    = Parser<P> && parser_type_v<P> == ParserType::NotChar;
template <class P> concept IsLiteral    = Parser<P> && parser_type_v<P> == ParserType::Literal;
template <class P> concept IsChoice     = Parser<P> && parser_type_v<P> == ParserType::Choice;
template <class P> concept IsSequence   = Parser<P> && parser_type_v<P> == ParserType::Sequence;
template <class P> concept IsOneOrMore  = Parser<P> && parser_type_v<P> == ParserType::OneOrMore;
template <class P> concept IsZeroOrMore = Parser<P> && parser_type_v<P> == ParserType::ZeroOrMore;
template <class P> concept IsMaybe      = Parser<P> && parser_type_v<P> == ParserType::Maybe;
template <class P> concept IsTransform  = Parser<P> && parser_type_v<P> == ParserType::Transform;
template <class P> concept IsJoin       = Parser<P> && parser_type_v<P> == ParserType::Join;
template <class P> concept IsIgnore     = Parser<P> && parser_type_v<P> == ParserType::Ignore;
template <class P> concept IsDelimit    = Parser<P> && parser_type_v<P> == ParserType::Delimit;
template <class P> concept IsCustom     = Parser<P> && parser_type_v<P> == ParserType::Custom;



template <static_string str>          requires (str.unique_and_sorted()) && (str.ascii()) && (str.size() != 0)   struct OneChar;
template <static_string str>          requires (str.unique_and_sorted()) && (str.ascii()) && (str.size() != 0)   struct NotChar;
template <static_string str>          requires (str.ascii()) && (str.size() != 0)                                struct Literal;
template <Parser... Ps>               requires (sizeof...(Ps) >= 2) && mp::all_same<typename Ps::result_type...> struct Choice;
template <Parser... Ps>               requires (sizeof...(Ps) >= 2)                                              struct Sequence;
template <Parser P>                                                                                              struct OneOrMore; 
template <Parser P>                                                                                              struct ZeroOrMore;
template <Parser P>                                                                                              struct Maybe;
template <Parser P, auto function>    requires std::invocable<decltype(function), typename P::result_type>       struct Transform;
template <Parser P>                   requires Joinable<typename P::result_type>                                 struct Join;
template <Parser P>                                                                                              struct Ignore;
template <Parser P, Parser Delimiter>                                                                            struct Delimit;
template <class CRTP>                                                                                            struct Custom;
struct CustomBase {};



template <static_string str>               constexpr ParserType parser_type_v<OneChar<str>>           = ParserType::OneChar;
template <static_string str>               constexpr ParserType parser_type_v<NotChar<str>>           = ParserType::NotChar;
template <static_string str>               constexpr ParserType parser_type_v<Literal<str>>           = ParserType::Literal;
template <Parser... Ps>                    constexpr ParserType parser_type_v<Choice<Ps...>>          = ParserType::Choice;
template <Parser... Ps>                    constexpr ParserType parser_type_v<Sequence<Ps...>>        = ParserType::Sequence;
template <Parser P>                        constexpr ParserType parser_type_v<OneOrMore<P>>           = ParserType::OneOrMore;
template <Parser P>                        constexpr ParserType parser_type_v<ZeroOrMore<P>>          = ParserType::ZeroOrMore;
template <Parser P>                        constexpr ParserType parser_type_v<Maybe<P>>               = ParserType::Maybe;
template <Parser P, auto function>         constexpr ParserType parser_type_v<Transform<P, function>> = ParserType::Transform;
template <Parser P>                        constexpr ParserType parser_type_v<Join<P>>                = ParserType::Join;
template <Parser P>                        constexpr ParserType parser_type_v<Ignore<P>>              = ParserType::Ignore;
template <Parser P, Parser Delimiter>      constexpr ParserType parser_type_v<Delimit<P, Delimiter>>  = ParserType::Delimit;
template <std::derived_from<CustomBase> P> constexpr ParserType parser_type_v<P>                      = ParserType::Custom;



TOK3N_END_NAMESPACE()
