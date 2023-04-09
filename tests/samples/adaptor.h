#pragma once
#include <tok3n/tok3n.h>
#include "samples/basic.h"
#include "samples/repeat.h"

TOK3N_BEGIN_NAMESPACE(tests::samples::all)

using namespace basic;

namespace
{
	using _21 = ABC;
	using _22 = OneOrMore<ABC>;
	using _23 = Maybe<Choice<ABC, QQ>>;
	using _24 = Sequence<ABC, ZeroOrMore<QQ>>;
	using _25 = Sequence<OneOrMore<ABC>, Maybe<Choice<ABC, QQ>>>;
}

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

TOK3N_END_NAMESPACE(tests::samples::all)
