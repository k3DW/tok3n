# Copyright 2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

include(${CMAKE_CURRENT_LIST_DIR}/gcc_and_clang.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wduplicated-cond \
    -Wduplicated-branches \
    -Wlogical-op \
    -Wuseless-cast \
")
