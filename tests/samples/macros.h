#pragma once
#include "framework/Assert.h"
#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/compound.h"
#include "samples/divergent.h"
#include "samples/repeat.h"



#define IMPL_DO_TO_SAMPLES_ALL(F) \
	DO_TO_SAMPLES_ADAPTOR(F)      \
	DO_TO_SAMPLES_BASIC(F)        \
	DO_TO_SAMPLES_COMPOUND(F)     \
	DO_TO_SAMPLES_DIVERGENT(F)    \
	DO_TO_SAMPLES_REPEAT(F)

#define DO_TO_SAMPLES_ALL(F)      \
	{                             \
		IMPL_DO_TO_SAMPLES_ALL(F) \
	} REQUIRE_SEMICOLON



#define EMPTY()
#define DEFER(...) __VA_ARGS__ EMPTY()

#define ADD_LPAREN(...) __VA_ARGS__ (
#define ADD_RPAREN(...) __VA_ARGS__ )
#define ADD_COMMA(...) __VA_ARGS__ ,

#define IMPL_DO_TO_SAMPLES_ALL_2(F2, X) \
	IMPL_DO_TO_SAMPLES_ALL(F2 DEFER(ADD_LPAREN)() X ADD_COMMA() ADD_RPAREN)

#define DO_TO_SAMPLES_ALL_2(F2) \
	IDENTITY(IDENTITY(IMPL_DO_TO_SAMPLES_ALL(IMPL_DO_TO_SAMPLES_ALL_2 DEFER(ADD_LPAREN)() F2 ADD_COMMA() ADD_RPAREN)))
