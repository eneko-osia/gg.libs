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
