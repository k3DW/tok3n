file(GLOB_RECURSE integral_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_configure_ide("${integral_test_files}")



add_executable(int_tests
    ${integral_test_files}
)

target_compile_definitions(int_tests PRIVATE VALUE_TYPE_INT)

tok3n_configure_target(int_tests PUBLIC)

target_include_directories(int_tests PUBLIC ..)

target_link_libraries(int_tests PUBLIC k3::tok3n)
target_link_libraries(int_tests PUBLIC framework)
target_link_libraries(int_tests PUBLIC Boost::preprocessor)

target_precompile_headers(int_tests PRIVATE samples.h)



add_executable(enum_tests
    ${integral_test_files}
)

target_compile_definitions(enum_tests PRIVATE VALUE_TYPE_ENUM)

tok3n_configure_target(enum_tests PUBLIC)

target_include_directories(enum_tests PUBLIC ..)

target_link_libraries(enum_tests PUBLIC k3::tok3n)
target_link_libraries(enum_tests PUBLIC framework)
target_link_libraries(enum_tests PUBLIC Boost::preprocessor)

target_precompile_headers(enum_tests PRIVATE samples.h)



set_target_properties(int_tests
    PROPERTIES
        FOLDER tests
)

set_target_properties(enum_tests
    PROPERTIES
        FOLDER tests
)
