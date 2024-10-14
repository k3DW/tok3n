// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once

#include "framework.h"

#include "common/asserts/Concept.h"
#include "common/asserts/Constructible.h"
#include "common/asserts/Equality.h"
#include "common/asserts/Operation.h"
#include "common/asserts/Parse.h"

#include "common/underlying.h"
#include "common/wrappers.h"

#include <k3/tok3n.h>

#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>
#include <source_location>
#include <unordered_map>
#include <vector>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
