add_subdirectory(framework)

file(GLOB_RECURSE tests_files
     LIST_DIRECTORIES false
     "asserts/*.h"
     "samples/*.ipp"
     "char-tests/*.h"
     "char-tests/*.cpp"
     "enum-tests/*.h"
     "enum-tests/*.cpp"
     "int-tests/*.h"
     "int-tests/*.cpp"
     "op_equals-tests/*.h"
     "op_equals-tests/*.cpp"
     "structural-tests/*.h"
     "structural-tests/*.cpp"
     "wchar_t-tests/*.h"
     "wchar_t-tests/*.cpp"
     "asserts.h"
     "pch.cpp"
     "pch.h"
     "underlying.h"
     "wrappers.h"
)

add_executable(tests
    ${tests_files}
)

set_target_properties(tests
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(tests PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_include_directories(tests PUBLIC .)

target_link_libraries(tests PUBLIC k3::tok3n)
target_link_libraries(tests PUBLIC framework)
target_link_libraries(tests PUBLIC Boost::preprocessor)

target_precompile_headers(tests PRIVATE pch.h)



if (tok3n_SETUP_IDE)

    foreach(_source IN ITEMS ${tests_files})
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
