# Copyright 2024-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(common INTERFACE)
target_sources(common INTERFACE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/include/common.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/asserts/Concept.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/asserts/Constructible.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/asserts/Equality.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/asserts/Operation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/asserts/Parse.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/underlying.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/common/wrappers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/adaptor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/basic-char.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/basic-non-char.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/classes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/compound.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/divergent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/functions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/helpers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/macros-char.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/macros-common.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/macros-non-char.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/repeat.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/samples/sub_parsers.hpp
)

tok3n_configure_source_group(common)

target_include_directories(common INTERFACE include)

target_link_libraries(common INTERFACE framework)
target_link_libraries(common INTERFACE Boost::preprocessor)

target_precompile_headers(common INTERFACE include/common.hpp)

set_target_properties(common
    PROPERTIES
        FOLDER tests
)
