# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.libs VERSION 0.0.1 LANGUAGES C CXX)

# directories
set(DOC_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/doc")
set(SRC_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TOOLS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools")

# libraries
set(LIBRARIES
    "core"
    "test"
    "app"
    "config"
    "log"
    "gfx"
    "gui"
)

# modules path
set(CMAKE_MODULE_PATH "${TOOLS_DIRECTORY}/cmake/modules" ${CMAKE_MODULE_PATH})

# includes
include(CMakeDependentOption)
include(GGFunctions)
include(GGSystem)

# options
option(GG_CORE "core library" ON)
option(GG_TEST "test library" ON)

# dependent libraries
cmake_dependent_option(GG_APP    "app library"    ON GG_CORE       OFF)
cmake_dependent_option(GG_CONFIG "config library" ON GG_CORE       OFF)
cmake_dependent_option(GG_LOG    "log library"    ON GG_CORE       OFF)
cmake_dependent_option(GG_GFX    "gfx library"    ON GG_APP;GG_LOG OFF)

# dependent documentation and testing
cmake_dependent_option(GG_ENABLE_DOC     "enable documentation" ON GG_CORE OFF)
cmake_dependent_option(GG_ENABLE_TESTING "enable tests"         ON GG_TEST OFF)

# configure version file
configure_file(
    "${TOOLS_DIRECTORY}/cmake/version/version.h.in"
    "${SRC_DIRECTORY}/core/include/gg/core/version.h"
)

# set global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# documentation
if (GG_ENABLE_DOC)
    # includes
    include(GGDoxygen)

    # add documentaion source directories
    foreach(LIBRARY ${LIBRARIES})
        string(TOUPPER ${LIBRARY} LIBRARY_UPPER)
        if(GG_${LIBRARY_UPPER})
            set(DOXYGEN_SRC_DIRECTORY ${DOXYGEN_SRC_DIRECTORY} "${SRC_DIRECTORY}/${LIBRARY}")
        endif()
    endforeach()

    # clean doxygen source directory
    string(REPLACE ";" " " DOXYGEN_SRC_DIRECTORY "${DOXYGEN_SRC_DIRECTORY}")

    # configure doxyfile
    configure_file(
        "${TOOLS_DIRECTORY}/cmake/doxygen/doxyfile.in"
        "${DOC_DIRECTORY}/doxyfile"
    )

    # add doc target
    add_custom_target(
        gg.docs
        COMMAND ${DOXYGEN_EXECUTABLE} "${DOC_DIRECTORY}/doxyfile"
        WORKING_DIRECTORY ${DOC_DIRECTORY}
        COMMENT "Generating documentation..."
        VERBATIM
    )

    # group folder
    set_target_properties(gg.docs PROPERTIES FOLDER gg.libs.docs)
endif()

# testing
if(GG_ENABLE_TESTING)
    # enable testing
    enable_testing()

    # include catch test parser
    include(catch/Catch)
endif()

# subdirectories
foreach(LIBRARY ${LIBRARIES})
    string(TOUPPER ${LIBRARY} LIBRARY_UPPER)
    if(GG_${LIBRARY_UPPER})
        add_subdirectory(${SRC_DIRECTORY}/${LIBRARY})
    endif()
endforeach()
