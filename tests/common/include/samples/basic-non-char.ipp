#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Any1 = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(A, C)>;    constexpr Any1 any1;
using Any2 = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(B, D)>;    constexpr Any2 any2;
#else
using Any1 = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(A, B, C)>; constexpr Any1 any1;
using Any2 = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(B, C, D)>; constexpr Any2 any2;
#endif
using Any3 = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(X, Y, Z)>; constexpr Any3 any3;
using Any4 = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(B, C)>;    constexpr Any4 any4;

#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Non1 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(A, C)>;    constexpr Non1 none1;
using Non2 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(B, D)>;    constexpr Non2 none2;
#else
using Non1 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(A, B, C)>; constexpr Non1 none1;
using Non2 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(B, C, D)>; constexpr Non2 none2;
#endif
using Non3 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(X, Y, Z)>; constexpr Non3 none3;
using Non4 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(B, C)>;    constexpr Non4 none4;
using Non5 = k3::tok3n::detail::none_of_parser<k3::tok3n::detail::static_array(Z)>;       constexpr Non5 none5;

using All1 = k3::tok3n::detail::all_of_parser<k3::tok3n::detail::static_array(X, Y, Z)>; constexpr All1 all1;
using All2 = k3::tok3n::detail::all_of_parser<k3::tok3n::detail::static_array(Y, Z)>;    constexpr All2 all2;
using All3 = k3::tok3n::detail::all_of_parser<k3::tok3n::detail::static_array(A, B)>;    constexpr All3 all3;

using Eps1 = k3::tok3n::detail::epsilon_parser<::value_type>;  constexpr Eps1 eps1;
using Ant1 = k3::tok3n::detail::anything_parser<::value_type>; constexpr Ant1 ant1;

using QQ       = k3::tok3n::detail::all_of_parser<k3::tok3n::detail::static_array(Question, Question)>; constexpr QQ       qq;
using ABC      = k3::tok3n::detail::all_of_parser<k3::tok3n::detail::static_array(A, B, C)>;            constexpr ABC      abc;
using Comma    = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(Com)>;                constexpr Comma    comma;
using SpaceDot = k3::tok3n::detail::any_of_parser<k3::tok3n::detail::static_array(Space, Dot)>;         constexpr SpaceDot spacedot;

#define BASIC_SAMPLES                  \
	(Any1) (Any2) (Any3) (Any4)        \
	(Non1) (Non2) (Non3) (Non4) (Non5) \
	(All1) (All2) (All3)               \
	(Eps1) (Ant1)                      \
	(QQ) (ABC) (Comma) (SpaceDot)
