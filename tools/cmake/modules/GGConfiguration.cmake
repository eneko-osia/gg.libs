#===============================================================================

set(build_configuration_types "debug;release;distribution")
set(CMAKE_CONFIGURATION_TYPES ${build_configuration_types}
    CACHE STRING "Build configuration types" FORCE)

set(CMAKE_CXX_FLAGS_DISTRIBUTION
    ${CMAKE_CXX_FLAGS_RELEASE}
    CACHE INTERNAL "cxx distribution compiler flags" FORCE)

set(CMAKE_EXE_LINKER_FLAGS_DISTRIBUTION
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE}
    CACHE INTERNAL "cxx distribution linker flags" FORCE)

#===============================================================================

if(NOT(CMAKE_BUILD_TYPE STREQUAL "debug" OR
       CMAKE_BUILD_TYPE STREQUAL "release" OR
       CMAKE_BUILD_TYPE STREQUAL "distribution"))
    set(CMAKE_BUILD_TYPE "debug"
        CACHE STRING "Build type [${build_configuration_types}]" FORCE)
endif()

#===============================================================================
