#include "pch.h"

namespace
{

enum
{
	A = 0,
	B = 1,
	C = 2,
};

constexpr int func(int lhs, int rhs)
{
	return lhs * 10 + rhs;
}

#define FN(X, Y) + func(X, Y)

#define DO_TO_ENUM(F) F(A) F(B) F(C)

#define IMPL_DO_TO_ENUM_2(F2, X) \
	DO_TO_ENUM(F2 DEFER(ADD_LPAREN)() X ADD_COMMA() ADD_RPAREN)

#define DO_TO_ENUM_2(F2) \
	IDENTITY(IDENTITY(DO_TO_ENUM(IMPL_DO_TO_ENUM_2 DEFER(ADD_LPAREN)() F2 ADD_COMMA() ADD_RPAREN)))

constexpr auto test_value = 0 + DO_TO_ENUM_2(FN);
static_assert(test_value == 99);

}
