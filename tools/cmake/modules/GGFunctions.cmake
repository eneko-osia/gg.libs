#===============================================================================

function(create_groups base_dir files_to_group)
    foreach(file_to_group IN LISTS files_to_group)
        get_filename_component(file_directory "${file_to_group}" DIRECTORY)
        string(REPLACE "${base_dir}" "" group "${file_directory}")
        string(REPLACE "/" "\\" group "${group}")
        source_group("${group}" FILES "${file_to_group}")
    endforeach()
endfunction()

#===============================================================================

function(generate_src_files base_dir)
    set(filename "${base_dir}/GGSrcFiles.cmake")
    file(WRITE "${filename}" "# @generated - run cmake configure to generate this file\n\n")

    list(APPEND include_file_extensions "h" "hpp")
    list(APPEND src_file_extensions "h" "hpp" "c" "cpp")
    write_files_in_folder(${filename} ${base_dir} "include" "${include_file_extensions}")
    write_files_in_folder(${filename} ${base_dir} "src" "${src_file_extensions}")
    write_files_in_folder(${filename} ${base_dir} "test" "${src_file_extensions}")

    file(APPEND "${filename}" "# groups\n")
    file(APPEND "${filename}" "create_groups(\${CMAKE_CURRENT_SOURCE_DIR} \"\${include_files}\")\n")
    file(APPEND "${filename}" "create_groups(\${CMAKE_CURRENT_SOURCE_DIR} \"\${src_files}\")\n")
    file(APPEND "${filename}" "create_groups(\${CMAKE_CURRENT_SOURCE_DIR} \"\${test_files}\")\n")
endfunction()

#===============================================================================

function(write_files_in_folder filename base_dir directory extensions)
    foreach(extension ${extensions})
        list(APPEND globbing_expressions "${base_dir}/${directory}/*.${extension}")
    endforeach()

    file(GLOB_RECURSE files ${globbing_expressions})
    if(NOT files STREQUAL "")
        file(APPEND "${filename}" "# ${directory} files\n")
        file(APPEND "${filename}" "set(${directory}_files\n")
        foreach(file ${files})
            string(REPLACE "${base_dir}" "\${CMAKE_CURRENT_SOURCE_DIR}" file "${file}")
            file(APPEND "${filename}" "    \"${file}\"\n")
        endforeach()
        file(APPEND "${filename}" ")\n")
    endif()
endfunction()

#===============================================================================

#===============================================================================
