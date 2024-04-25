#pragma once

using Any1 = AnyOf<StaticArray(E::A, E::B, E::C)>; constexpr Any1 any1;
using Any2 = AnyOf<StaticArray(E::B, E::C, E::D)>; constexpr Any2 any2;
using Any3 = AnyOf<StaticArray(E::X, E::Y, E::Z)>; constexpr Any3 any3;
using Any4 = AnyOf<StaticArray(E::C, E::D)>;       constexpr Any4 any4;

using Non1 = NoneOf<StaticArray(E::A, E::B, E::C)>; constexpr Non1 none1;
using Non2 = NoneOf<StaticArray(E::B, E::C, E::D)>; constexpr Non2 none2;
using Non3 = NoneOf<StaticArray(E::X, E::Y, E::Z)>; constexpr Non3 none3;
using Non4 = NoneOf<StaticArray(E::C, E::D)>;       constexpr Non4 none4;
using Non5 = NoneOf<StaticArray(E::Z)>;             constexpr Non5 none5;

using All1 = AllOf<StaticArray(E::X, E::Y, E::Z)>; constexpr All1 all1;
using All2 = AllOf<StaticArray(E::Y, E::Z)>;       constexpr All2 all2;
using All3 = AllOf<StaticArray(E::A, E::B)>;       constexpr All3 all3;

using Eps1 = Epsilon<int>;  constexpr Eps1 eps1;
using Ant1 = Anything<int>; constexpr Ant1 ant1;

using QQ       = AllOf<StaticArray(E::Question, E::Question)>; constexpr QQ       qq;
using ABC      = AllOf<StaticArray(E::A, E::B, E::C)>;         constexpr ABC      abc;
using Comma    = AnyOf<StaticArray(E::Com)>;                   constexpr Comma    comma;
using SpaceDot = AnyOf<StaticArray(E::Space, E::Dot)>;         constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3)               \
	(Eps1) (Ant1)                      \
	(QQ) (ABC) (Comma) (SpaceDot)
