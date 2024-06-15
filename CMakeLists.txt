cmake_minimum_required (VERSION 3.22)

project (k3_tok3n
         VERSION 0
         LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(tools/tok3n_configure.cmake)

add_library(k3_tok3n INTERFACE
    "$<$<CXX_COMPILER_ID:MSVC>:tools/tok3n.natvis>"
)
add_library(k3::tok3n ALIAS k3_tok3n)

target_include_directories(k3_tok3n INTERFACE include)

tok3n_configure_target(k3_tok3n INTERFACE)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

option (tok3n_BUILD_TESTS "Build tests" OFF)
option (tok3n_BUILD_EXAMPLES "Build examples" OFF)
option (tok3n_SETUP_IDE "Organize the projects for IDEs" OFF)



#--------------------------------------------
#   Tests
#--------------------------------------------
if (tok3n_BUILD_TESTS)
    enable_testing()
    add_subdirectory(external/boostorg/preprocessor)
    add_subdirectory(tests)
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

    tok3n_configure_ide("${list_of_files}")
    source_group("" FILES "src/main.cpp")

    add_executable(tok3n
        ${list_of_files}
        "src/main.cpp"
    )
    
    tok3n_configure_target(tok3n PUBLIC)

    target_include_directories(tok3n PUBLIC include)

endif()
