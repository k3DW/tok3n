#pragma once
#include <k3/tok3n.h>
#include "samples/adaptor.h"
#include "samples/basic.h"

using Cho1 = Choice<L4, NC4>;      constexpr Cho1 cho1;
using Cho2 = Choice<NC4, L4>;      constexpr Cho2 cho2;
using Cho3 = Choice<L4, OC4, NC5>; constexpr Cho3 cho3;
using Cho4 = Choice<NC5, L4, OC4>; constexpr Cho4 cho4;
using Cho5 = Choice<Ign1, Ign2>;   constexpr Cho5 cho5;

using Seq1 = Sequence<L4, NC4>;      constexpr Seq1 seq1;
using Seq2 = Sequence<NC4, L4>;      constexpr Seq2 seq2;
using Seq3 = Sequence<L4, OC4, NC5>; constexpr Seq3 seq3;
using Seq4 = Sequence<NC5, L4, OC4>; constexpr Seq4 seq4;
using Seq5 = Sequence<Ign1, Ign2>;   constexpr Seq5 seq5;

#define COMPOUND_SAMPLES               \
	(Cho1) (Cho2) (Cho3) (Cho4) (Cho5) \
	(Seq1) (Seq2) (Seq3) (Seq4) (Seq5)
