#pragma once
#include <k3/tok3n.h>
#include "samples/basic.h"
#include "samples/sub_parsers.h"
#include "framework/parser_list.h"

namespace k3::tok3n::tests {

using May1 = Maybe<_11>; constexpr May1 may1;
using May2 = Maybe<_12>; constexpr May2 may2;
using May3 = Maybe<_13>; constexpr May3 may3;
using May4 = Maybe<_14>; constexpr May4 may4;

using Exa1 = Exactly<_11, 3>; constexpr Exa1 exa1;
using Exa2 = Exactly<_12, 5>; constexpr Exa2 exa2;
using Exa3 = Exactly<_13, 4>; constexpr Exa3 exa3;
using Exa4 = Exactly<_14, 2>; constexpr Exa4 exa4;

using Oom1 = OneOrMore<_11>; constexpr Oom1 oom1;
using Oom2 = OneOrMore<_12>; constexpr Oom2 oom2;
using Oom3 = OneOrMore<_13>; constexpr Oom3 oom3;
using Oom4 = OneOrMore<_14>; constexpr Oom4 oom4;

using Zom1 = ZeroOrMore<_11>; constexpr Zom1 zom1;
using Zom2 = ZeroOrMore<_12>; constexpr Zom2 zom2;
using Zom3 = ZeroOrMore<_13>; constexpr Zom3 zom3;
using Zom4 = ZeroOrMore<_14>; constexpr Zom4 zom4;

using Del1 = Delimit<ABC, Comma, std::false_type>;    constexpr Del1 del1;
using Del2 = Delimit<ABC, SpaceDot, std::false_type>; constexpr Del2 del2;
using Del3 = Delimit<QQ, Comma, std::false_type>;     constexpr Del3 del3;
using Del4 = Delimit<QQ, SpaceDot, std::false_type>;  constexpr Del4 del4;
using Del5 = Delimit<Comma, ABC, std::false_type>;    constexpr Del5 del5;
using Del6 = Delimit<SpaceDot, ABC, std::false_type>; constexpr Del6 del6;
using Del7 = Delimit<Comma, QQ, std::false_type>;     constexpr Del7 del7;
using Del8 = Delimit<SpaceDot, QQ, std::false_type>;  constexpr Del8 del8;

using Dek1 = Delimit<ABC, Comma, std::true_type>;    constexpr Dek1 dek1;
using Dek2 = Delimit<ABC, SpaceDot, std::true_type>; constexpr Dek2 dek2;
using Dek3 = Delimit<QQ, Comma, std::true_type>;     constexpr Dek3 dek3;
using Dek4 = Delimit<QQ, SpaceDot, std::true_type>;  constexpr Dek4 dek4;
using Dek5 = Delimit<Comma, ABC, std::true_type>;    constexpr Dek5 dek5;
using Dek6 = Delimit<SpaceDot, ABC, std::true_type>; constexpr Dek6 dek6;
using Dek7 = Delimit<Comma, QQ, std::true_type>;     constexpr Dek7 dek7;
using Dek8 = Delimit<SpaceDot, QQ, std::true_type>;  constexpr Dek8 dek8;

constexpr auto repeat_list = parser_list(
	may1, may2, may3, may4,
	exa1, exa2, exa3, exa4,
	oom1, oom2, oom3, oom4,
	zom1, zom2, zom3, zom4,
	del1, del2, del3, del4, del5, del6, del7, del8,
	dek1, dek2, dek3, dek4, dek5, dek6, dek7, dek8
);

} // namespace k3::tok3n::tests
