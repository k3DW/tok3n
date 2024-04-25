#pragma once

using Any1 = AnyOf<StaticArray(SS::A, SS::C)>;        constexpr Any1 any1;
using Any2 = AnyOf<StaticArray(SS::B, SS::D)>;        constexpr Any2 any2;
using Any3 = AnyOf<StaticArray(SS::X, SS::Y, SS::Z)>; constexpr Any3 any3;
using Any4 = AnyOf<StaticArray(SS::B, SS::C)>;        constexpr Any4 any4;

using Non1 = NoneOf<StaticArray(SS::A, SS::C)>;        constexpr Non1 none1;
using Non2 = NoneOf<StaticArray(SS::B, SS::D)>;        constexpr Non2 none2;
using Non3 = NoneOf<StaticArray(SS::X, SS::Y, SS::Z)>; constexpr Non3 none3;
using Non4 = NoneOf<StaticArray(SS::B, SS::C)>;        constexpr Non4 none4;
using Non5 = NoneOf<StaticArray(SS::Z)>;               constexpr Non5 none5;

using All1 = AllOf<StaticArray(SS::X, SS::Y, SS::Z)>; constexpr All1 all1;
using All2 = AllOf<StaticArray(SS::Y, SS::Z)>;        constexpr All2 all2;
using All3 = AllOf<StaticArray(SS::A, SS::B)>;        constexpr All3 all3;

using Eps1 = Epsilon<S>;  constexpr Eps1 eps1;
using Ant1 = Anything<S>; constexpr Ant1 ant1;

using QQ       = AllOf<StaticArray(SS::Question, SS::Question)>; constexpr QQ       qq;
using ABC      = AllOf<StaticArray(SS::A, SS::B, SS::C)>;        constexpr ABC      abc;
using Comma    = AnyOf<StaticArray(SS::Com)>;                    constexpr Comma    comma;
using SpaceDot = AnyOf<StaticArray(SS::Space, SS::Dot)>;         constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3)               \
	(Eps1) (Ant1)                      \
	(QQ) (ABC) (Comma) (SpaceDot)
