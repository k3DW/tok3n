#pragma once

#include <k3/tok3n/parsers/adaptor/Ignore.h>
#include <k3/tok3n/parsers/adaptor/Complete.h>

#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>
#include <k3/tok3n/parsers/basic/Literal.h>

#include <k3/tok3n/parsers/compound/Choice.h>
#include <k3/tok3n/parsers/compound/Sequence.h>

#include <k3/tok3n/parsers/divergent/Join.h>
#include <k3/tok3n/parsers/divergent/Transform.h>
#include <k3/tok3n/parsers/divergent/ApplyTransform.h>
#include <k3/tok3n/parsers/divergent/Into.h>
#include <k3/tok3n/parsers/divergent/ApplyInto.h>
#include <k3/tok3n/parsers/divergent/Constant.h>
#include <k3/tok3n/parsers/divergent/Defaulted.h>
#include <k3/tok3n/parsers/divergent/Custom.h>

#include <k3/tok3n/parsers/repeat/Maybe.h>
#include <k3/tok3n/parsers/repeat/Exactly.h>
#include <k3/tok3n/parsers/repeat/OneOrMore.h>
#include <k3/tok3n/parsers/repeat/ZeroOrMore.h>
#include <k3/tok3n/parsers/repeat/Delimit.h>

#include <k3/tok3n/parsers/optimizations/JoinOneOrMoreBasic.h>
