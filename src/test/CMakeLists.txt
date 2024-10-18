# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.test
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
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
        $<$<STREQUAL:${COMPILER},gnu>:-fexceptions>
        $<$<STREQUAL:${COMPILER},gnu>:-Wall>
        $<$<STREQUAL:${COMPILER},gnu>:-Werror>
        $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
        $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
        $<$<STREQUAL:${COMPILER},msvc>:/EHsc>
        $<$<STREQUAL:${COMPILER},msvc>:/W4>
        $<$<STREQUAL:${COMPILER},msvc>:/WX>
)

# group folder
set_target_properties(gg.test PROPERTIES FOLDER gg.libs)
