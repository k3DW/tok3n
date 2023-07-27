#pragma once
#include <k3/tok3n.h>
#include "samples/basic.h"
#include "samples/sub_parsers.h"
#include "framework/parser_list.h"

using Ign1 = Ignore<_21>; constexpr Ign1 ign1;
using Ign2 = Ignore<_22>; constexpr Ign2 ign2;
using Ign3 = Ignore<_23>; constexpr Ign3 ign3;
using Ign4 = Ignore<_24>; constexpr Ign4 ign4;
using Ign5 = Ignore<_25>; constexpr Ign5 ign5;

using Com1 = Complete<_11>;             constexpr Com1 com1;
using Com2 = Complete<_12>;             constexpr Com2 com2;
using Com3 = Complete<_13>;             constexpr Com3 com3;
using Com4 = Complete<_14>;             constexpr Com4 com4;
using Com5 = Complete<Maybe<_14>>;      constexpr Com5 com5;
using Com6 = Complete<OneOrMore<_14>>;  constexpr Com6 com6;
using Com7 = Complete<ZeroOrMore<_14>>; constexpr Com7 com7;

constexpr auto adaptor_list = parser_list(
	ign1, ign2, ign3, ign4, ign5,
	com1, com2, com3, com4, com5, com6, com7
);

#define DO_TO_SAMPLES_ADAPTOR(F)                            \
	F(Ign1) F(Ign2) F(Ign3) F(Ign4) F(Ign5)                 \
	F(Com1) F(Com2) F(Com3) F(Com4) F(Com5) F(Com6) F(Com7)
