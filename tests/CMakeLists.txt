add_subdirectory(framework)
add_subdirectory(char-tests)
add_subdirectory(integral-tests)
add_subdirectory(object-tests)



file(GLOB_RECURSE tests_files
     LIST_DIRECTORIES false
     "asserts/*.h"
     "samples/*.ipp"
     "asserts.h"
     "pch.cpp"
     "pch.h"
     "underlying.h"
     "wrappers.h"
)

tok3n_configure_ide("${tests_files}")



add_executable(tests
    ${tests_files}
)

tok3n_configure_target(tests PUBLIC)

target_include_directories(tests PUBLIC .)

target_link_libraries(tests PUBLIC k3::tok3n)
target_link_libraries(tests PUBLIC framework)
target_link_libraries(tests PUBLIC Boost::preprocessor)

target_precompile_headers(tests PRIVATE pch.h)

set_target_properties(tests
    PROPERTIES
        FOLDER tests
)
