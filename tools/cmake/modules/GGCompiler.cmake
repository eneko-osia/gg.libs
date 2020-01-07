#===============================================================================

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(compiler "clang" CACHE STRING "Build compiler" FORCE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(compiler "gnu" CACHE STRING "Build compiler" FORCE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(compiler "msvc" CACHE STRING "Build compiler" FORCE)
else()
    message(FATAL_ERROR "Unsuported c++ compiler [${CMAKE_CXX_COMPILER_ID}]")
endif()

#===============================================================================
