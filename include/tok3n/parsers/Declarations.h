#pragma once
#include "tok3n/utilities/meta.h"
#include "tok3n/utilities/static_string.h"
#include "tok3n/parsers/Details.h"

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



template <class T>
requires (not std::is_reference_v<T>)
class Result;

template <class R, class T> constexpr bool is_result_v = false;
template <class T>          constexpr bool is_result_v<Result<T>, T> = true;

template <class R, class T> concept IsResult = is_result_v<R, T>;

template <class P>
concept Parser =
	(parser_type_v<P> != ParserType::None) &&
	(std::is_empty_v<P>) &&
	mp::implicitly_default_constructible<P> &&
	requires { typename P::result_type; } &&
	requires (Input input)
	{
		{ P::parse(input) } -> IsResult<typename P::result_type>;
		{ P::lookahead(input) } -> IsResult<void>;
	};



template <class M> constexpr bool is_modifier_v           = false;
template <class M> constexpr bool is_modifier_v <const M> = is_modifier_v<M>;
template <class M> constexpr bool is_modifier_v <M&>      = is_modifier_v<M>;
template <class M> constexpr bool is_modifier_v <M&&>     = is_modifier_v<M>;

template <class M>
concept Modifier = is_modifier_v<M> && std::is_empty_v<M>;



template <class P, ParserType type>
concept IsParser = Parser<P> && parser_type_v<P> == type;

template <class P> concept IsOneChar        = IsParser<P, ParserType::OneChar>;
template <class P> concept IsNotChar        = IsParser<P, ParserType::NotChar>;
template <class P> concept IsLiteral        = IsParser<P, ParserType::Literal>;
template <class P> concept IsChoice         = IsParser<P, ParserType::Choice>;
template <class P> concept IsSequence       = IsParser<P, ParserType::Sequence>;
template <class P> concept IsOneOrMore      = IsParser<P, ParserType::OneOrMore>;
template <class P> concept IsZeroOrMore     = IsParser<P, ParserType::ZeroOrMore>;
template <class P> concept IsMaybe          = IsParser<P, ParserType::Maybe>;
template <class P> concept IsExactly        = IsParser<P, ParserType::Exactly>;
template <class P> concept IsIgnore         = IsParser<P, ParserType::Ignore>;
template <class P> concept IsTransform      = IsParser<P, ParserType::Transform>;
template <class P> concept IsApplyTransform = IsParser<P, ParserType::ApplyTransform>;
template <class P> concept IsJoin           = IsParser<P, ParserType::Join>;
template <class P> concept IsDelimit        = IsParser<P, ParserType::Delimit>;
template <class P> concept IsInto           = IsParser<P, ParserType::Into>;
template <class P> concept IsApplyInto      = IsParser<P, ParserType::ApplyInto>;
template <class P> concept IsConstant       = IsParser<P, ParserType::Constant>;
template <class P> concept IsDefaulted      = IsParser<P, ParserType::Defaulted>;
template <class P> concept IsComplete       = IsParser<P, ParserType::Complete>;
template <class P> concept IsCustom         = IsParser<P, ParserType::Custom>;



template <static_string str>          requires detail::SingleChar_able<str>             struct OneChar;
template <static_string str>          requires detail::SingleChar_able<str>             struct NotChar;
template <static_string str>          requires detail::Literal_able<str>                struct Literal;
template <Parser... Ps>               requires detail::Choice_able<Ps...>               struct Choice;
template <Parser... Ps>               requires detail::Sequence_able<Ps...>             struct Sequence;
template <Parser P>                   requires detail::OneOrMore_able<P>                struct OneOrMore;
template <Parser P>                   requires detail::ZeroOrMore_able<P>               struct ZeroOrMore;
template <Parser P>                   requires detail::Maybe_able<P>                    struct Maybe;
template <Parser P, std::size_t N>    requires detail::Exactly_able<P, N>               struct Exactly;
template <Parser P>                                                                     struct Ignore;
template <Parser P, auto function>    requires detail::Transform_able<P, function>      struct Transform;
template <Parser P, auto function>    requires detail::ApplyTransform_able<P, function> struct ApplyTransform;
template <Parser P>                   requires detail::Join_able<P>                     struct Join;
template <Parser P, Parser Delimiter> requires detail::Delimit_able<P, Delimiter>       struct Delimit;
template <Parser P, class T>          requires detail::Into_able<P, T>                  struct Into;
template <Parser P, class T>          requires detail::ApplyInto_able<P, T>             struct ApplyInto;
template <Parser P, auto value>                                                         struct Constant;
template <Parser P, class T>          requires std::is_default_constructible_v<T>       struct Defaulted;
template <Parser P>                                                                     struct Complete;
template <class CRTP>                                                                   struct Custom;
namespace detail { template <class P> concept IsDerivedFromCustom = std::is_base_of_v<Custom<P>, P>; }



template <static_string str>               constexpr ParserType parser_type_v<OneChar<str>>                = ParserType::OneChar;
template <static_string str>               constexpr ParserType parser_type_v<NotChar<str>>                = ParserType::NotChar;
template <static_string str>               constexpr ParserType parser_type_v<Literal<str>>                = ParserType::Literal;
template <Parser... Ps>                    constexpr ParserType parser_type_v<Choice<Ps...>>               = ParserType::Choice;
template <Parser... Ps>                    constexpr ParserType parser_type_v<Sequence<Ps...>>             = ParserType::Sequence;
template <Parser P>                        constexpr ParserType parser_type_v<OneOrMore<P>>                = ParserType::OneOrMore;
template <Parser P>                        constexpr ParserType parser_type_v<ZeroOrMore<P>>               = ParserType::ZeroOrMore;
template <Parser P>                        constexpr ParserType parser_type_v<Maybe<P>>                    = ParserType::Maybe;
template <Parser P, std::size_t N>         constexpr ParserType parser_type_v<Exactly<P, N>>               = ParserType::Exactly;
template <Parser P>                        constexpr ParserType parser_type_v<Ignore<P>>                   = ParserType::Ignore;
template <Parser P, auto function>         constexpr ParserType parser_type_v<Transform<P, function>>      = ParserType::Transform;
template <Parser P, auto function>         constexpr ParserType parser_type_v<ApplyTransform<P, function>> = ParserType::ApplyTransform;
template <Parser P>                        constexpr ParserType parser_type_v<Join<P>>                     = ParserType::Join;
template <Parser P, Parser Delimiter>      constexpr ParserType parser_type_v<Delimit<P, Delimiter>>       = ParserType::Delimit;
template <Parser P, class T>               constexpr ParserType parser_type_v<Into<P, T>>                  = ParserType::Into;
template <Parser P, class T>               constexpr ParserType parser_type_v<ApplyInto<P, T>>             = ParserType::ApplyInto;
template <Parser P, auto value>            constexpr ParserType parser_type_v<Constant<P, value>>          = ParserType::Constant;
template <Parser P, class T>               constexpr ParserType parser_type_v<Defaulted<P, T>>             = ParserType::Defaulted;
template <Parser P>                        constexpr ParserType parser_type_v<Complete<P>>                 = ParserType::Complete;
template <detail::IsDerivedFromCustom P>   constexpr ParserType parser_type_v<P>                           = ParserType::Custom;



TOK3N_END_NAMESPACE()
