#===============================================================================

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(platform "android" CACHE STRING "Build platform" FORCE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(platform "mac" CACHE STRING "Build platform" FORCE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(platform "linux" CACHE STRING "Build platform" FORCE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(platform "windows" CACHE STRING "Build platform" FORCE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
    set(platform "uwp" CACHE STRING "Build platform" FORCE)
else()
    message(FATAL_ERROR "Unsuported build platform [${CMAKE_SYSTEM_NAME}]")
endif()

#===============================================================================

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(platform_architecture "x86_64" CACHE STRING "Build architecture" FORCE)
else()
    set(platform_architecture "x86" CACHE STRING "Build architecture" FORCE)
endif()

#===============================================================================
