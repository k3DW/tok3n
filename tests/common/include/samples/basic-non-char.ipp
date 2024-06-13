#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Any1 = AnyOf<StaticArray(A, C)>;    constexpr Any1 any1;
using Any2 = AnyOf<StaticArray(B, D)>;    constexpr Any2 any2;
#else
using Any1 = AnyOf<StaticArray(A, B, C)>; constexpr Any1 any1;
using Any2 = AnyOf<StaticArray(B, C, D)>; constexpr Any2 any2;
#endif
using Any3 = AnyOf<StaticArray(X, Y, Z)>; constexpr Any3 any3;
using Any4 = AnyOf<StaticArray(B, C)>;    constexpr Any4 any4;

#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Non1 = NoneOf<StaticArray(A, C)>;    constexpr Non1 none1;
using Non2 = NoneOf<StaticArray(B, D)>;    constexpr Non2 none2;
#else
using Non1 = NoneOf<StaticArray(A, B, C)>; constexpr Non1 none1;
using Non2 = NoneOf<StaticArray(B, C, D)>; constexpr Non2 none2;
#endif
using Non3 = NoneOf<StaticArray(X, Y, Z)>; constexpr Non3 none3;
using Non4 = NoneOf<StaticArray(B, C)>;    constexpr Non4 none4;
using Non5 = NoneOf<StaticArray(Z)>;       constexpr Non5 none5;

using All1 = AllOf<StaticArray(X, Y, Z)>; constexpr All1 all1;
using All2 = AllOf<StaticArray(Y, Z)>;    constexpr All2 all2;
using All3 = AllOf<StaticArray(A, B)>;    constexpr All3 all3;

using Eps1 = Epsilon<::value_type>;  constexpr Eps1 eps1;
using Ant1 = Anything<::value_type>; constexpr Ant1 ant1;

using QQ       = AllOf<StaticArray(Question, Question)>; constexpr QQ       qq;
using ABC      = AllOf<StaticArray(A, B, C)>;            constexpr ABC      abc;
using Comma    = AnyOf<StaticArray(Com)>;                constexpr Comma    comma;
using SpaceDot = AnyOf<StaticArray(Space, Dot)>;         constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3)               \
	(Eps1) (Ant1)                      \
	(QQ) (ABC) (Comma) (SpaceDot)
