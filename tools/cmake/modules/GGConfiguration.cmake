#===============================================================================

set(build_configuration_types "debug;release;distribution")
set(CMAKE_CONFIGURATION_TYPES ${build_configuration_types}
    CACHE STRING "Build configuration types" FORCE)

set(CMAKE_C_FLAGS_DISTRIBUTION
    ${CMAKE_CXX_FLAGS_RELEASE}
    CACHE STRING "c distribution compiler flags" FORCE)

set(CMAKE_CXX_FLAGS_DISTRIBUTION
    ${CMAKE_CXX_FLAGS_RELEASE}
    CACHE STRING "cxx distribution compiler flags" FORCE)

set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTION
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE}
    CACHE STRING "cxx distribution linker flags" FORCE)

#===============================================================================

foreach(configuration ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${configuration} upper_configuration)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${upper_configuration}
        ${CMAKE_BINARY_DIR}/lib/${platform}/${platform_architecture}/${configuration}
        CACHE INTERNAL "Archive output directory [${configuration}]" FORCE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${upper_configuration}
        ${CMAKE_BINARY_DIR}/lib/${platform}/${platform_architecture}/${configuration}
        CACHE INTERNAL "Library output directory [${configuration}]" FORCE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${upper_configuration}
        ${CMAKE_BINARY_DIR}/bin/${platform}/${platform_architecture}/${configuration}
        CACHE INTERNAL "Runtime output directory [${configuration}]" FORCE)
endforeach()

#===============================================================================

if(NOT(CMAKE_BUILD_TYPE STREQUAL "debug" OR
       CMAKE_BUILD_TYPE STREQUAL "release" OR
       CMAKE_BUILD_TYPE STREQUAL "distribution"))
    set(CMAKE_BUILD_TYPE "debug"
        CACHE STRING "Build type [${build_configuration_types}]" FORCE)
endif()

#===============================================================================
