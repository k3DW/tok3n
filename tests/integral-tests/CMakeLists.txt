file(GLOB_RECURSE integral_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_configure_ide("${integral_test_files}")



add_executable(int_tests
    ${integral_test_files}
)

tok3n_configure_test_target(int_tests VALUE_TYPE_INT)



add_executable(enum_tests
    ${integral_test_files}
)

tok3n_configure_test_target(enum_tests VALUE_TYPE_ENUM)
