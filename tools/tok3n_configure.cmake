function(tok3n_configure_source_group target)

    get_target_property(list_of_files ${target} SOURCES)

    foreach(_source IN ITEMS ${list_of_files})
        if(${_source} MATCHES "^\\$<") # Skip any unevaluated generator expressions
            continue()
        endif()
        get_filename_component(_source_path "${_source}" DIRECTORY)
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()

    if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/cmake_pch.cxx")
        # https://stackoverflow.com/questions/71070320/cmake-how-to-group-generated-precompiled-headers-in-visual-studio
        source_group("_cmake_generated" FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/cmake_pch.cxx")
        foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
            source_group("_cmake_generated" FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/${config_type}/cmake_pch.hxx")
        endforeach()
    endif()

endfunction()
