
file(GLOB_RECURSE json_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

add_executable(json
    ${json_files}
)

set_target_properties(json
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        FOLDER examples
)

target_compile_options(json PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_link_libraries(json PUBLIC k3::tok3n)



if (tok3n_SETUP_IDE)

    foreach(_source IN ITEMS ${json_files})
        get_filename_component(_source_path "${_source}" PATH)
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()

endif()
