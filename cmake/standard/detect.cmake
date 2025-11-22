# Copyright 2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

if("cxx_std_23" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    include(${CMAKE_CURRENT_LIST_DIR}/23.cmake)
else()
    include(${CMAKE_CURRENT_LIST_DIR}/20.cmake)
endif()
