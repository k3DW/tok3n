#pragma once

#define ASSEMBLY "wchar_t"
#define TT(x) L ## x
using value_type = wchar_t;

using namespace k3::tok3n;

#include "samples/helpers.ipp"

#include "samples/basic-char.ipp"
#include "samples/sub_parsers.ipp"

#include "samples/classes.ipp"
#include "samples/functions.ipp"
#include "samples/macros-char.ipp"

#include "samples/adaptor.ipp"
#include "samples/compound.ipp"
#include "samples/divergent.ipp"
#include "samples/repeat.ipp"
