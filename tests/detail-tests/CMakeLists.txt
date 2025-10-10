# Copyright 2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

tok3n_add_basic_test_executable(detail_tests detail
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpo/get.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpo/optional_like.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpo/span_like.cpp
)
