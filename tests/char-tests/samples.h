#pragma once
#include "common.h"

#if defined(VALUE_TYPE_CHAR)

    #if defined(VALUE_TYPE_WCHAR_T)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    #define TT(x) x
    using value_type = char;

#elif defined(VALUE_TYPE_WCHAR_T)

    #if defined(VALUE_TYPE_CHAR)
    #error Can only define one VALUE_TYPE_XYZ macro.
    #endif

    #define TT(x) L ## x
    using value_type = wchar_t;

#else
#error Must define exactly one VALUE_TYPE_XYZ macro.
#endif

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
