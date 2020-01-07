#===============================================================================

find_package(Python3 COMPONENTS Interpreter REQUIRED)
if(NOT Python3_Interpreter_FOUND)
    message(FATAL_ERROR "Python3 interpreter could not be found")
endif()

#===============================================================================

function(add_generate_src_files_command target base_dir)
    add_custom_command(
        TARGET ${target}
        PRE_BUILD
        COMMAND ${Python3_EXECUTABLE}
        ${gg_tools_directory}/cmake/python/generate_src_files.py
        WORKING_DIRECTORY ${base_dir}
        COMMENT "Generating GGSrcFiles.cmake files"
        VERBATIM
    )
endfunction()

#===============================================================================

function(generate_src_files base_dir)
    execute_process(
        COMMAND ${Python3_EXECUTABLE}
        ${gg_tools_directory}/cmake/python/generate_src_files.py
        WORKING_DIRECTORY ${base_dir}
    )
endfunction()

#===============================================================================
