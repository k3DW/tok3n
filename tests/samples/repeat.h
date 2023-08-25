#pragma once
#include <k3/tok3n.h>
#include "samples/basic.h"
#include "samples/sub_parsers.h"

using May1 = Maybe<_11>; constexpr May1 may1;
using May2 = Maybe<_12>; constexpr May2 may2;
using May3 = Maybe<_13>; constexpr May3 may3;
using May4 = Maybe<_14>; constexpr May4 may4;

using Exa1 = Exactly<_11, Index<3>>; constexpr Exa1 exa1;
using Exa2 = Exactly<_12, Index<5>>; constexpr Exa2 exa2;
using Exa3 = Exactly<_13, Index<4>>; constexpr Exa3 exa3;
using Exa4 = Exactly<_14, Index<2>>; constexpr Exa4 exa4;

using Oom1 = OneOrMore<_11>; constexpr Oom1 oom1;
using Oom2 = OneOrMore<_12>; constexpr Oom2 oom2;
using Oom3 = OneOrMore<_13>; constexpr Oom3 oom3;
using Oom4 = OneOrMore<_14>; constexpr Oom4 oom4;

using Zom1 = ZeroOrMore<_11>; constexpr Zom1 zom1;
using Zom2 = ZeroOrMore<_12>; constexpr Zom2 zom2;
using Zom3 = ZeroOrMore<_13>; constexpr Zom3 zom3;
using Zom4 = ZeroOrMore<_14>; constexpr Zom4 zom4;

using Del1 = Delimit<ABC, Comma, False>;    constexpr Del1 del1;
using Del2 = Delimit<ABC, SpaceDot, False>; constexpr Del2 del2;
using Del3 = Delimit<QQ, Comma, False>;     constexpr Del3 del3;
using Del4 = Delimit<QQ, SpaceDot, False>;  constexpr Del4 del4;
using Del5 = Delimit<Comma, ABC, False>;    constexpr Del5 del5;
using Del6 = Delimit<SpaceDot, ABC, False>; constexpr Del6 del6;
using Del7 = Delimit<Comma, QQ, False>;     constexpr Del7 del7;
using Del8 = Delimit<SpaceDot, QQ, False>;  constexpr Del8 del8;

using Dek1 = Delimit<ABC, Comma, True>;    constexpr Dek1 dek1;
using Dek2 = Delimit<ABC, SpaceDot, True>; constexpr Dek2 dek2;
using Dek3 = Delimit<QQ, Comma, True>;     constexpr Dek3 dek3;
using Dek4 = Delimit<QQ, SpaceDot, True>;  constexpr Dek4 dek4;
using Dek5 = Delimit<Comma, ABC, True>;    constexpr Dek5 dek5;
using Dek6 = Delimit<SpaceDot, ABC, True>; constexpr Dek6 dek6;
using Dek7 = Delimit<Comma, QQ, True>;     constexpr Dek7 dek7;
using Dek8 = Delimit<SpaceDot, QQ, True>;  constexpr Dek8 dek8;

#define REPEAT_SAMPLES                                      \
	(May1) (May2) (May3) (May4)                             \
	(Exa1) (Exa2) (Exa3) (Exa4)                             \
	(Oom1) (Oom2) (Oom3) (Oom4)                             \
	(Zom1) (Zom2) (Zom3) (Zom4)                             \
	(Del1) (Del2) (Del3) (Del4) (Del5) (Del6) (Del7) (Del8) \
	(Dek1) (Dek2) (Dek3) (Dek4) (Dek5) (Dek6) (Dek7) (Dek8)
