#include "pch.h"
#include "int-samples/int-samples.h"

using namespace E;

FIXTURE("Epsilon");

TEST("Epsilon", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Eps1, int);

	ASSERT_IS_PARSER(Eps1, int, EpsilonFamily, void);
}

TEST("Epsilon", "Parse")
{
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(A, B, C), e(A, B, C));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(A, C, B), e(A, C, B));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(B, A, C), e(B, A, C));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(B, C, A), e(B, C, A));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(C, A, B), e(C, A, B));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(C, B, A), e(C, B, A));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(X, Y, Z), e(X, Y, Z));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(X, Z, Y), e(X, Z, Y));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(Y, X, Z), e(Y, X, Z));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(Y, Z, X), e(Y, Z, X));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(Z, X, Y), e(Z, X, Y));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(Z, Y, X), e(Z, Y, X));
	ASSERT_PARSE_SUCCESS_VOID(Eps1, e(), e());
}
