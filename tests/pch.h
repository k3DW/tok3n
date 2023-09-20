#pragma once

#include <format>
#include <map>
#include <numeric>
#include <string>
#include <string_view>
#include <source_location>
#include <unordered_map>
#include <vector>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

#include <k3/tok3n.h>

#include "framework/Assert.h"
#include "framework/Error.h"
#include "framework/Fixture.h"
#include "framework/Runner.h"
#include "framework/StringBuilder.h"
#include "framework/Test.h"
#include "framework/TestResult.h"
#include "framework/underlying.h"

#include "asserts/Concept.h"
#include "asserts/Constructible.h"
#include "asserts/Equality.h"
#include "asserts/Operation.h"
#include "asserts/Parse.h"

using namespace k3::tok3n;

#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/compound.h"
#include "samples/divergent.h"
#include "samples/functions.h"
#include "samples/macros.h"
#include "samples/repeat.h"
#include "samples/wrappers.h"
