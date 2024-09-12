using Ign1 = k3::tok3n::Ignore<_21>; constexpr Ign1 ign1;
using Ign2 = k3::tok3n::Ignore<_22>; constexpr Ign2 ign2;
using Ign3 = k3::tok3n::Ignore<_23>; constexpr Ign3 ign3;
using Ign4 = k3::tok3n::Ignore<_24>; constexpr Ign4 ign4;
using Ign5 = k3::tok3n::Ignore<_25>; constexpr Ign5 ign5;

using Com1 = k3::tok3n::Complete<_11>;                        constexpr Com1 com1;
using Com2 = k3::tok3n::Complete<_12>;                        constexpr Com2 com2;
using Com3 = k3::tok3n::Complete<_13>;                        constexpr Com3 com3;
using Com4 = k3::tok3n::Complete<_14>;                        constexpr Com4 com4;
using Com5 = k3::tok3n::Complete<k3::tok3n::Maybe<_14>>;      constexpr Com5 com5;
using Com6 = k3::tok3n::Complete<k3::tok3n::OneOrMore<_14>>;  constexpr Com6 com6;
using Com7 = k3::tok3n::Complete<k3::tok3n::ZeroOrMore<_14>>; constexpr Com7 com7;

using Nam1 = k3::tok3n::Named<_21, "nam1">; constexpr Nam1 nam1;
using Nam2 = k3::tok3n::Named<_22, "nam2">; constexpr Nam2 nam2;
using Nam3 = k3::tok3n::Named<_23, "nam3">; constexpr Nam3 nam3;
using Nam4 = k3::tok3n::Named<_24, "nam4">; constexpr Nam4 nam4;

#define ADAPTOR_SAMPLES                              \
	(Ign1) (Ign2) (Ign3) (Ign4) (Ign5)               \
	(Com1) (Com2) (Com3) (Com4) (Com5) (Com6) (Com7) \
	(Nam1) (Nam2) (Nam3) (Nam4)
