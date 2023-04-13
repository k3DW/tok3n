#pragma once
#include <k3/tok3n.h>
#include "samples/basic.h"

TOK3N_BEGIN_NAMESPACE(tests)

using Cho1 = Choice<L4, NC4>;      constexpr Cho1 cho1;
using Cho2 = Choice<NC4, L4>;      constexpr Cho2 cho2;
using Cho3 = Choice<L4, OC4, NC5>; constexpr Cho3 cho3;
using Cho4 = Choice<NC5, L4, OC4>; constexpr Cho4 cho4;

using Seq1 = Sequence<L4, NC4>;      constexpr Seq1 seq1;
using Seq2 = Sequence<NC4, L4>;      constexpr Seq2 seq2;
using Seq3 = Sequence<L4, OC4, NC5>; constexpr Seq3 seq3;
using Seq4 = Sequence<NC5, L4, OC4>; constexpr Seq4 seq4;

TOK3N_END_NAMESPACE(tests)
