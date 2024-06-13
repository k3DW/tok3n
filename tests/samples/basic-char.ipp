using Any1 = AnyOf<TT("abc")>; constexpr Any1 any1;
using Any2 = AnyOf<TT("bcd")>; constexpr Any2 any2;
using Any3 = AnyOf<TT("xyz")>; constexpr Any3 any3;
using Any4 = AnyOf<TT("cd")>;  constexpr Any4 any4;

using Non1 = NoneOf<TT("abc")>; constexpr Non1 none1;
using Non2 = NoneOf<TT("bcd")>; constexpr Non2 none2;
using Non3 = NoneOf<TT("xyz")>; constexpr Non3 none3;
using Non4 = NoneOf<TT("cd")>;  constexpr Non4 none4;
using Non5 = NoneOf<TT("z")>;   constexpr Non5 none5;

using All1 = AllOf<TT("literal")>; constexpr All1 all1;
using All2 = AllOf<TT("ly")>;      constexpr All2 all2;
using All3 = AllOf<TT("test")>;    constexpr All3 all3;
using All4 = AllOf<TT("ab")>;      constexpr All4 all4;

using Eps1 = Epsilon<::value_type>;  constexpr Eps1 eps1;
using Ant1 = Anything<::value_type>; constexpr Ant1 ant1;

using QQ       = AllOf<TT("??")>;  constexpr QQ       qq;
using ABC      = AllOf<TT("abc")>; constexpr ABC      abc;
using Comma    = AnyOf<TT(",")>;   constexpr Comma    comma;
using SpaceDot = AnyOf<TT(" .")>;  constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3) (All4)        \
	(Eps1) (Ant1)                      \
	(QQ) (ABC) (Comma) (SpaceDot)
