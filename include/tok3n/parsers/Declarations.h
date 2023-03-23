#pragma once
#include "tok3n/utilities/meta.h"
#include "tok3n/utilities/static_string.h"
#include "tok3n/concepts/IsResult.h"
#include "tok3n/concepts/implicitly_default_constructible.h"
#include "tok3n/concepts/Parser.h"
#include "tok3n/concepts/IsParser.h"
#include "tok3n/types/ParserType.h"
#include "tok3n/parsers/Details.h"

TOK3N_BEGIN_NAMESPACE()



template <class M> constexpr bool is_modifier_v           = false;
template <class M> constexpr bool is_modifier_v <const M> = is_modifier_v<M>;
template <class M> constexpr bool is_modifier_v <M&>      = is_modifier_v<M>;
template <class M> constexpr bool is_modifier_v <M&&>     = is_modifier_v<M>;

template <class M>
concept Modifier = is_modifier_v<M> && std::is_empty_v<M>;



TOK3N_END_NAMESPACE()
