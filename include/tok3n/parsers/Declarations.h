#pragma once
#include "tok3n/utilities/meta.h"
#include "tok3n/utilities/static_string.h"
#include "tok3n/concepts/IsResult.h"
#include "tok3n/concepts/implicitly_default_constructible.h"
#include "tok3n/concepts/Parser.h"
#include "tok3n/types/ParserType.h"
#include "tok3n/parsers/Details.h"

TOK3N_BEGIN_NAMESPACE()



template <class M> constexpr bool is_modifier_v           = false;
template <class M> constexpr bool is_modifier_v <const M> = is_modifier_v<M>;
template <class M> constexpr bool is_modifier_v <M&>      = is_modifier_v<M>;
template <class M> constexpr bool is_modifier_v <M&&>     = is_modifier_v<M>;

template <class M>
concept Modifier = is_modifier_v<M> && std::is_empty_v<M>;



template <class P, ParserType type>
concept IsParser = Parser<P> && P::type == type;

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



TOK3N_END_NAMESPACE()
