#pragma once

namespace E
{
    constexpr int A = -1002;
    constexpr int B = -1001;
    constexpr int C = -1000;
    constexpr int D = -999;
    constexpr int X = 0;
    constexpr int Y = 10;
    constexpr int Z = 20;
    constexpr int Question = 100;
    constexpr int Com = 1000;
    constexpr int Space = 10000;
    constexpr int Dot = 100000;
};

#define ASSEMBLY "int"
using value_type = int;

using namespace k3::tok3n;

#include "samples/helpers.ipp"

#include "samples/basic-integral.ipp"
#include "samples/sub_parsers.ipp"

#include "samples/classes.ipp"
#include "samples/functions.ipp"
#include "samples/macros-integral.ipp"

#include "samples/adaptor.ipp"
#include "samples/compound.ipp"
#include "samples/divergent.ipp"
#include "samples/repeat.ipp"

using namespace E;
