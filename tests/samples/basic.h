#pragma once
#include <k3/tok3n.h>

TOK3N_BEGIN_NAMESPACE(tests)

using OC1 = OneChar<"abc">;     constexpr OC1 oc1;
using OC2 = OneChar<"bcd">;     constexpr OC2 oc2;
using OC3 = OneChar<"xyz">;     constexpr OC3 oc3;
using NC1 = NotChar<"abc">;     constexpr NC1 nc1;
using NC2 = NotChar<"bcd">;     constexpr NC2 nc2;
using NC3 = NotChar<"xyz">;     constexpr NC3 nc3;
using L1  = Literal<"literal">; constexpr L1  l1;
using L2  = Literal<"ly">;      constexpr L2  l2;
using L3  = Literal<"test">;    constexpr L3  l3;

using OC4 = OneChar<"cd">; constexpr OC4 oc4;
using NC4 = NotChar<"cd">; constexpr NC4 nc4;
using NC5 = NotChar<"z">;  constexpr NC5 nc5;
using L4  = Literal<"ab">; constexpr L4  l4;

using QQ       = Literal<"??">;  constexpr QQ       qq;
using ABC      = Literal<"abc">; constexpr ABC      abc;
using Comma    = OneChar<",">;   constexpr Comma    comma;
using SpaceDot = OneChar<" .">;  constexpr SpaceDot spacedot;

TOK3N_END_NAMESPACE(tests)