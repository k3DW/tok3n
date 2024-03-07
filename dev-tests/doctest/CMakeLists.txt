
file(GLOB_RECURSE tests_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
     "../../external/doctest/doctest/**.cpp" # Not header only!!
)

add_executable(dev_doctest
    ${tests_files}
)

set_target_properties(dev_doctest
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        FOLDER dev-tests
)

target_compile_options(dev_doctest PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_include_directories(dev_doctest PUBLIC .)
target_include_directories(dev_doctest PUBLIC ../../external/doctest)

target_link_libraries(dev_doctest PUBLIC k3::tok3n)



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
