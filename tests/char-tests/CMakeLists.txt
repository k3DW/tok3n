file(GLOB_RECURSE char_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)



add_executable(char_tests
    ${char_test_files}
)

set_target_properties(char_tests
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(char_tests PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_include_directories(char_tests PUBLIC ..)

target_link_libraries(char_tests PUBLIC k3::tok3n)
target_link_libraries(char_tests PUBLIC framework)
target_link_libraries(char_tests PUBLIC Boost::preprocessor)

target_precompile_headers(char_tests PRIVATE samples.h)

target_compile_definitions(char_tests PRIVATE VALUE_TYPE_CHAR)



add_executable(wchar_t_tests
    ${char_test_files}
)

set_target_properties(wchar_t_tests
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(wchar_t_tests PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_include_directories(wchar_t_tests PUBLIC ..)

target_link_libraries(wchar_t_tests PUBLIC k3::tok3n)
target_link_libraries(wchar_t_tests PUBLIC framework)
target_link_libraries(wchar_t_tests PUBLIC Boost::preprocessor)

target_precompile_headers(wchar_t_tests PRIVATE samples.h)

target_compile_definitions(wchar_t_tests PRIVATE VALUE_TYPE_WCHAR_T)



if (tok3n_SETUP_IDE)

    foreach(_source IN ITEMS ${char_test_files})
        get_filename_component(_source_path "${_source}" PATH)
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()

    # https://stackoverflow.com/questions/71070320/cmake-how-to-group-generated-precompiled-headers-in-visual-studio
    source_group("_cmake_generated" FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/tests.dir/cmake_pch.cxx)
    foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
        source_group("_cmake_generated" FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/tests.dir/${config_type}/cmake_pch.hxx)
    endforeach()

endif()
