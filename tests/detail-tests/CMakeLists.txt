# Copyright 2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

tok3n_add_basic_test_executable(detail_tests detail
    main.cpp
    cpo/emplace.cpp
    cpo/get.cpp
    cpo/index.cpp
    cpo/optional_like.cpp
    cpo/push.cpp
    cpo/span_like.cpp
    cpo/tuple_like.cpp
    cpo/visit.cpp
)
