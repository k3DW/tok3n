#pragma once
#include <k3/tok3n.h>

using OC1 = AnyOf<"abc">;     constexpr OC1 oc1;
using OC2 = AnyOf<"bcd">;     constexpr OC2 oc2;
using OC3 = AnyOf<"xyz">;     constexpr OC3 oc3;
using NC1 = NoneOf<"abc">;     constexpr NC1 nc1;
using NC2 = NoneOf<"bcd">;     constexpr NC2 nc2;
using NC3 = NoneOf<"xyz">;     constexpr NC3 nc3;
using L1  = Literal<"literal">; constexpr L1  l1;
using L2  = Literal<"ly">;      constexpr L2  l2;
using L3  = Literal<"test">;    constexpr L3  l3;

using OC4 = AnyOf<"cd">; constexpr OC4 oc4;
using NC4 = NoneOf<"cd">; constexpr NC4 nc4;
using NC5 = NoneOf<"z">;  constexpr NC5 nc5;
using L4  = Literal<"ab">; constexpr L4  l4;

using QQ       = Literal<"??">;  constexpr QQ       qq;
using ABC      = Literal<"abc">; constexpr ABC      abc;
using Comma    = AnyOf<",">;   constexpr Comma    comma;
using SpaceDot = AnyOf<" .">;  constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                                  \
	(OC1) (OC2) (OC3) (NC1) (NC2) (NC3) (L1) (L2) (L3) \
	(OC4) (NC4) (NC5) (L4)                             \
	(QQ) (ABC) (Comma) (SpaceDot)
