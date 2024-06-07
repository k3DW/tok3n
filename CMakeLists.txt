cmake_minimum_required (VERSION 3.22)

project (k3_tok3n
         VERSION 0
         LANGUAGES CXX)

add_library(k3_tok3n INTERFACE
    "$<$<CXX_COMPILER_ID:MSVC>:tools/tok3n.natvis>"
)
add_library(k3::tok3n ALIAS k3_tok3n)

target_include_directories(k3_tok3n INTERFACE include)

set_target_properties(k3_tok3n PROPERTIES CXX_STANDARD 20)
target_compile_features(k3_tok3n INTERFACE cxx_std_20)

option (tok3n_BUILD_TESTS "Build tests" OFF)
option (tok3n_BUILD_EXAMPLES "Build examples" OFF)
option (tok3n_SETUP_IDE "Organize the projects for IDEs" OFF)



#--------------------------------------------
#   Tests
#--------------------------------------------
if (tok3n_BUILD_TESTS)
    add_subdirectory(tests)
    add_subdirectory(external/boostorg/preprocessor)
endif()



#--------------------------------------------
#   Examples
#--------------------------------------------
if (tok3n_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()



#--------------------------------------------
#   IDEs
#--------------------------------------------
if (tok3n_SETUP_IDE)

    file(GLOB_RECURSE list_of_files
        LIST_DIRECTORIES false
        "include/*.h"
    )

    add_executable(tok3n
        ${list_of_files}
        "src/main.cpp"
    )

    target_include_directories(tok3n PUBLIC include)

    set_target_properties(tok3n
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
    )

    source_group("" FILES "src/main.cpp")

    foreach(_source IN ITEMS ${list_of_files})
        get_filename_component(_source_path "${_source}" PATH)
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}/include/k3" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()

endif()
