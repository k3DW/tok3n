#pragma once
#include "char-samples/basic.h"
#include "char-samples/sub_parsers.h"

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

#define ADAPTOR_SAMPLES                              \
	(Ign1) (Ign2) (Ign3) (Ign4) (Ign5)               \
	(Com1) (Com2) (Com3) (Com4) (Com5) (Com6) (Com7)
