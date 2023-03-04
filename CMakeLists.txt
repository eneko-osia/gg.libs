# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.libs VERSION 0.0.1 LANGUAGES C CXX)

# variables
set(gg_directory
    ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE INTERNAL
    "GG directory"
    FORCE
)

set(gg_doc_directory
    ${gg_directory}/doc
    CACHE INTERNAL
    "GG documentation directory"
    FORCE
)

set(gg_src_directory
    ${gg_directory}/src
    CACHE INTERNAL
    "GG source directory"
    FORCE
)

set(gg_tools_directory
    ${gg_directory}/tools
    CACHE INTERNAL
    "GG tools directory"
    FORCE
)

set(gg_libraries
    "core"
    "test"
    "log"
    "app"
    "config"
    "gfx"
    "gui"
)

# modules path
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${gg_tools_directory}/cmake/modules
    CACHE INTERNAL
    "CMake module path"
    FORCE
)

# includes
include(CMakeDependentOption)
include(GGPlatform)
include(GGCompiler)
include(GGConfiguration)
include(GGFunctions)

# options
option(
    GG_CORE
    "core library"
    OFF
)

option(
    GG_TEST
    "test library"
    OFF
)

# dependent options
cmake_dependent_option(
    GG_APP
    "app library"
    OFF
    "GG_CORE"
    OFF
)

cmake_dependent_option(
    GG_CONFIG
    "config library"
    OFF
    "GG_CORE"
    OFF
)

cmake_dependent_option(
    GG_LOG
    "log library"
    OFF
    "GG_CORE"
    OFF
)

cmake_dependent_option(
    GG_GFX
    "gfx library"
    OFF
    "GG_APP;GG_APP_WINDOW_SUPPORT;GG_LOG"
    OFF
)

cmake_dependent_option(
    GG_GUI
    "gui library"
    OFF
    "GG_GFX"
    OFF
)

cmake_dependent_option(
    GG_LIBS_ENABLE_DOC
    "enable documentation"
    OFF
    "GG_CORE"
    OFF
)

cmake_dependent_option(
    GG_LIBS_ENABLE_TESTING
    "enable tests"
    OFF
    "GG_TEST"
    OFF
)

# configure version file
set(version_file_path ${gg_src_directory}/core/include/gg/core/version.h)
configure_file(
    ${gg_tools_directory}/cmake/version/version.h.in
    ${version_file_path} @ONLY
)

# set global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# documentation
if(GG_LIBS_ENABLE_DOC)
    # find doxygen dependency
    find_package(Doxygen REQUIRED)

    # add documentaion source directories
    foreach(library ${gg_libraries})
        string(TOUPPER ${library} upper_library)
        if(GG_${upper_library})
            set(doxygen_src_dir
                ${doxygen_src_dir}
                ${gg_src_directory}/${library}
            )
        endif()
    endforeach()

    # clean doxygen source directory
    string(REPLACE ";" " " doxygen_src_dir "${doxygen_src_dir}")

    # configure doxyfile
    configure_file(
        ${gg_tools_directory}/cmake/doxygen/doxyfile.in
        ${gg_doc_directory}/doxyfile @ONLY
    )

    # add doc target
    add_custom_target(
        gg.docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${gg_doc_directory}/doxyfile
        WORKING_DIRECTORY ${gg_doc_directory}
        COMMENT "Generating documentation..."
        VERBATIM
    )

    # group folder
    set_target_properties(gg.docs PROPERTIES FOLDER gg.libs.docs)
endif()

# testing
if(GG_LIBS_ENABLE_TESTING)
    # enable testing
    enable_testing()

    # include catch test parser
    include(catch/Catch)
endif()

# subdirectories
foreach(library ${gg_libraries})
    string(TOUPPER ${library} upper_library)
    if(GG_${upper_library})
        add_subdirectory(${gg_src_directory}/${library})
    endif()
endforeach()
