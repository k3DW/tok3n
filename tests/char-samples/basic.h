#pragma once
#include <k3/tok3n.h>

using Any1 = AnyOf<"abc">; constexpr Any1 any1;
using Any2 = AnyOf<"bcd">; constexpr Any2 any2;
using Any3 = AnyOf<"xyz">; constexpr Any3 any3;
using Any4 = AnyOf<"cd">;  constexpr Any4 any4;

using Non1 = NoneOf<"abc">; constexpr Non1 none1;
using Non2 = NoneOf<"bcd">; constexpr Non2 none2;
using Non3 = NoneOf<"xyz">; constexpr Non3 none3;
using Non4 = NoneOf<"cd">;  constexpr Non4 none4;
using Non5 = NoneOf<"z">;   constexpr Non5 none5;

using All1 = AllOf<"literal">; constexpr All1 all1;
using All2 = AllOf<"ly">;      constexpr All2 all2;
using All3 = AllOf<"test">;    constexpr All3 all3;
using All4 = AllOf<"ab">;      constexpr All4 all4;

using QQ       = AllOf<"??">;  constexpr QQ       qq;
using ABC      = AllOf<"abc">; constexpr ABC      abc;
using Comma    = AnyOf<",">;   constexpr Comma    comma;
using SpaceDot = AnyOf<" .">;  constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3) (All4)        \
	(QQ) (ABC) (Comma) (SpaceDot)
