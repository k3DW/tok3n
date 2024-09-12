using May1 = k3::tok3n::Maybe<_11>; constexpr May1 may1;
using May2 = k3::tok3n::Maybe<_12>; constexpr May2 may2;
using May3 = k3::tok3n::Maybe<_13>; constexpr May3 may3;
using May4 = k3::tok3n::Maybe<_14>; constexpr May4 may4;

using Exa1 = k3::tok3n::Exactly<_11, k3::tok3n::detail::index_c<3>>; constexpr Exa1 exa1;
using Exa2 = k3::tok3n::Exactly<_12, k3::tok3n::detail::index_c<5>>; constexpr Exa2 exa2;
using Exa3 = k3::tok3n::Exactly<_13, k3::tok3n::detail::index_c<4>>; constexpr Exa3 exa3;
using Exa4 = k3::tok3n::Exactly<_14, k3::tok3n::detail::index_c<2>>; constexpr Exa4 exa4;

using Oom1 = k3::tok3n::OneOrMore<_11>; constexpr Oom1 oom1;
using Oom2 = k3::tok3n::OneOrMore<_12>; constexpr Oom2 oom2;
using Oom3 = k3::tok3n::OneOrMore<_13>; constexpr Oom3 oom3;
using Oom4 = k3::tok3n::OneOrMore<_14>; constexpr Oom4 oom4;

using Zom1 = k3::tok3n::ZeroOrMore<_11>; constexpr Zom1 zom1;
using Zom2 = k3::tok3n::ZeroOrMore<_12>; constexpr Zom2 zom2;
using Zom3 = k3::tok3n::ZeroOrMore<_13>; constexpr Zom3 zom3;
using Zom4 = k3::tok3n::ZeroOrMore<_14>; constexpr Zom4 zom4;

using Del1 = k3::tok3n::Delimit<ABC, Comma, std::false_type>;    constexpr Del1 del1;
using Del2 = k3::tok3n::Delimit<ABC, SpaceDot, std::false_type>; constexpr Del2 del2;
using Del3 = k3::tok3n::Delimit<QQ, Comma, std::false_type>;     constexpr Del3 del3;
using Del4 = k3::tok3n::Delimit<QQ, SpaceDot, std::false_type>;  constexpr Del4 del4;
using Del5 = k3::tok3n::Delimit<Comma, ABC, std::false_type>;    constexpr Del5 del5;
using Del6 = k3::tok3n::Delimit<SpaceDot, ABC, std::false_type>; constexpr Del6 del6;
using Del7 = k3::tok3n::Delimit<Comma, QQ, std::false_type>;     constexpr Del7 del7;
using Del8 = k3::tok3n::Delimit<SpaceDot, QQ, std::false_type>;  constexpr Del8 del8;

using Dek1 = k3::tok3n::Delimit<ABC, Comma, std::true_type>;    constexpr Dek1 dek1;
using Dek2 = k3::tok3n::Delimit<ABC, SpaceDot, std::true_type>; constexpr Dek2 dek2;
using Dek3 = k3::tok3n::Delimit<QQ, Comma, std::true_type>;     constexpr Dek3 dek3;
using Dek4 = k3::tok3n::Delimit<QQ, SpaceDot, std::true_type>;  constexpr Dek4 dek4;
using Dek5 = k3::tok3n::Delimit<Comma, ABC, std::true_type>;    constexpr Dek5 dek5;
using Dek6 = k3::tok3n::Delimit<SpaceDot, ABC, std::true_type>; constexpr Dek6 dek6;
using Dek7 = k3::tok3n::Delimit<Comma, QQ, std::true_type>;     constexpr Dek7 dek7;
using Dek8 = k3::tok3n::Delimit<SpaceDot, QQ, std::true_type>;  constexpr Dek8 dek8;

#define REPEAT_SAMPLES                                      \
	(May1) (May2) (May3) (May4)                             \
	(Exa1) (Exa2) (Exa3) (Exa4)                             \
	(Oom1) (Oom2) (Oom3) (Oom4)                             \
	(Zom1) (Zom2) (Zom3) (Zom4)                             \
	(Del1) (Del2) (Del3) (Del4) (Del5) (Del6) (Del7) (Del8) \
	(Dek1) (Dek2) (Dek3) (Dek4) (Dek5) (Dek6) (Dek7) (Dek8)
