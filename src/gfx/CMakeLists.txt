# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
if(GG_OPENGL)
    include(GGOpenGL)
endif()

if(GG_VULKAN)
    include(GGVulkan)
endif()

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.gfx
    STATIC
        ${deps_files}
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.gfx
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(GG_OPENGL)
    target_include_directories(
        gg.gfx
        PUBLIC
            ${OPENGL_INCLUDE_DIR}
    )
endif()

if(GG_VULKAN)
    target_include_directories(
        gg.gfx
        PUBLIC
            ${Vulkan_INCLUDE_DIRS}
    )
endif()

# compile definitions
target_compile_definitions(
    gg.gfx
    PUBLIC
        GG_GFX
        $<$<IN_LIST:opengl,${gfx}>:GG_OPENGL>
        $<$<IN_LIST:vulkan,${gfx}>:GG_VULKAN>
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.gfx
    PRIVATE
        $<$<STREQUAL:${compiler},gnu>:-fno-exceptions>
        $<$<STREQUAL:${compiler},gnu>:-Wall>
        $<$<STREQUAL:${compiler},gnu>:-Wextra>
        $<$<STREQUAL:${compiler},gnu>:-Wpedantic>
        $<$<STREQUAL:${compiler},gnu>:-Werror>
        #$<$<STREQUAL:${compiler},msvc>:/EHs-c->
        $<$<STREQUAL:${compiler},msvc>:/W4>
        $<$<STREQUAL:${compiler},msvc>:/WX>
)

# link libraries
target_link_libraries(
    gg.gfx
    PUBLIC
        gg.app
        $<$<IN_LIST:opengl,${gfx}>:${OPENGL_LIBRARIES}>
        $<$<IN_LIST:vulkan,${gfx}>:${Vulkan_LIBRARIES}>
)

# group folder
set_target_properties(gg.gfx PROPERTIES FOLDER gg.libs)

# testing
if(GGLIBS_ENABLE_TESTING)
    # executable
    add_executable(gg.gfx.test ${test_files})

    # include directories
    target_include_directories(
        gg.gfx.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.gfx.test
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

    # link libraries
    target_link_libraries(gg.gfx.test gg.test gg.gfx)

    # group folder
    set_target_properties(gg.gfx.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    ParseAndAddCatchTests(gg.gfx.test)
endif()
