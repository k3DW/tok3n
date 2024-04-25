#pragma once

using Any1 = AnyOf<L"abc">; constexpr Any1 any1;
using Any2 = AnyOf<L"bcd">; constexpr Any2 any2;
using Any3 = AnyOf<L"xyz">; constexpr Any3 any3;
using Any4 = AnyOf<L"cd">;  constexpr Any4 any4;

using Non1 = NoneOf<L"abc">; constexpr Non1 none1;
using Non2 = NoneOf<L"bcd">; constexpr Non2 none2;
using Non3 = NoneOf<L"xyz">; constexpr Non3 none3;
using Non4 = NoneOf<L"cd">;  constexpr Non4 none4;
using Non5 = NoneOf<L"z">;   constexpr Non5 none5;

using All1 = AllOf<L"literal">; constexpr All1 all1;
using All2 = AllOf<L"ly">;      constexpr All2 all2;
using All3 = AllOf<L"test">;    constexpr All3 all3;
using All4 = AllOf<L"ab">;      constexpr All4 all4;

using Eps1 = Epsilon<wchar_t>;  constexpr Eps1 eps1;
using Ant1 = Anything<wchar_t>; constexpr Ant1 ant1;

using QQ       = AllOf<L"??">;  constexpr QQ       qq;
using ABC      = AllOf<L"abc">; constexpr ABC      abc;
using Comma    = AnyOf<L",">;   constexpr Comma    comma;
using SpaceDot = AnyOf<L" .">;  constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3) (All4)        \
	(Eps1) (Ant1)                      \
	(QQ) (ABC) (Comma) (SpaceDot)
