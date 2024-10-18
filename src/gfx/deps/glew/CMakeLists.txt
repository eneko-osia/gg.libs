# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.glew
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.glew
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.glew
    PUBLIC
        GG_GLEW
        GLEW_NO_GLU
        GLEW_STATIC
    PRIVATE
        $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.glew
    PUBLIC
        $<$<STREQUAL:${COMPILER},gnu>:-Wno-address>
    PRIVATE
        $<$<STREQUAL:${COMPILER},gnu>:-fno-exceptions>
        $<$<STREQUAL:${COMPILER},gnu>:-Wall>
        $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
        $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
        $<$<STREQUAL:${COMPILER},gnu>:-Werror>
        $<$<STREQUAL:${COMPILER},msvc>:/EHs-c->
        $<$<STREQUAL:${COMPILER},msvc>:/W4>
        $<$<STREQUAL:${COMPILER},msvc>:/WX>
)

# link libraries
target_link_libraries(
    gg.glew
)

# group folder
set_target_properties(gg.glew PROPERTIES FOLDER gg.gfx.deps)
