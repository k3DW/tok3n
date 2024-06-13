file(GLOB_RECURSE char_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_configure_ide("${char_test_files}")



add_executable(char_tests
    ${char_test_files}
)

target_compile_definitions(char_tests PRIVATE VALUE_TYPE_CHAR)

tok3n_configure_target(char_tests PUBLIC)

target_include_directories(char_tests PUBLIC ..)

target_link_libraries(char_tests PUBLIC k3::tok3n)
target_link_libraries(char_tests PUBLIC framework)
target_link_libraries(char_tests PUBLIC Boost::preprocessor)

target_precompile_headers(char_tests PRIVATE samples.h)



add_executable(wchar_t_tests
    ${char_test_files}
)

target_compile_definitions(wchar_t_tests PRIVATE VALUE_TYPE_WCHAR_T)

tok3n_configure_target(wchar_t_tests PUBLIC)

target_include_directories(wchar_t_tests PUBLIC ..)

target_link_libraries(wchar_t_tests PUBLIC k3::tok3n)
target_link_libraries(wchar_t_tests PUBLIC framework)
target_link_libraries(wchar_t_tests PUBLIC Boost::preprocessor)

target_precompile_headers(wchar_t_tests PRIVATE samples.h)



set_target_properties(char_tests
    PROPERTIES
        FOLDER tests
)

set_target_properties(wchar_t_tests
    PROPERTIES
        FOLDER tests
)
