# Copyright 2024-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(common INTERFACE)
target_sources(common INTERFACE FILE_SET headers TYPE HEADERS FILES
    include/common.hpp
    include/common/asserts/Concept.hpp
    include/common/asserts/Constructible.hpp
    include/common/asserts/Equality.hpp
    include/common/asserts/Operation.hpp
    include/common/asserts/Parse.hpp
    include/common/underlying.hpp
    include/common/wrappers.hpp
    include/samples/adaptor.hpp
    include/samples/basic-char.hpp
    include/samples/basic-non-char.hpp
    include/samples/classes.hpp
    include/samples/compound.hpp
    include/samples/divergent.hpp
    include/samples/functions.hpp
    include/samples/helpers.hpp
    include/samples/macros-char.hpp
    include/samples/macros-common.hpp
    include/samples/macros-non-char.hpp
    include/samples/repeat.hpp
    include/samples/sub_parsers.hpp
)

target_include_directories(common INTERFACE include)

target_link_libraries(common INTERFACE framework)
target_link_libraries(common INTERFACE Boost::preprocessor)

target_precompile_headers(common INTERFACE include/common.hpp)

set_target_properties(common
    PROPERTIES
        FOLDER tests
)
