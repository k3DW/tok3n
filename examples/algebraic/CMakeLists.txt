# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_executable(algebraic
    algebraic.cpp
)
target_sources(algebraic PRIVATE FILE_SET headers TYPE HEADERS FILES
    evaluate.hpp
    parser.hpp
    print.hpp
)

set_target_properties(algebraic
    PROPERTIES
        FOLDER examples
)

target_link_libraries(algebraic PRIVATE k3::tok3n)
