# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.test
    STATIC
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.test
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/deps
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.test
    PUBLIC
        GG_TEST
)

# compile options
target_compile_options(
    gg.test
    PRIVATE
        $<$<STREQUAL:${compiler},gnu>:-fexceptions>
        $<$<STREQUAL:${compiler},gnu>:-Wall>
        $<$<STREQUAL:${compiler},gnu>:-Wextra>
        $<$<STREQUAL:${compiler},gnu>:-Wpedantic>
        $<$<STREQUAL:${compiler},gnu>:-Werror>
        $<$<STREQUAL:${compiler},msvc>:/EHsc>
        $<$<STREQUAL:${compiler},msvc>:/W4>
        $<$<STREQUAL:${compiler},msvc>:/WX>
)

# group folder
set_target_properties(gg.test PROPERTIES FOLDER gg.libs)
