# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# options
option(
    GG_GFX_OPENGL_SUPPORT
    "gfx opengl support"
    OFF
)

option(
    GG_GFX_VULKAN_SUPPORT
    "gfx vulkan support"
    OFF
)

# includes
if(GG_GFX_OPENGL_SUPPORT)
    include(GGOpenGL)
endif()

if(GG_GFX_VULKAN_SUPPORT)
    include(GGVulkan)
endif()

include(GGSrcFiles.cmake)

# add dependencies
if(GG_GFX_OPENGL_SUPPORT)
    add_subdirectory("deps/glew")
endif()

# library
add_library(
    gg.gfx
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.gfx
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(GG_GFX_OPENGL_SUPPORT)
    target_include_directories(
        gg.gfx
        PRIVATE
            ${OPENGL_INCLUDE_DIR}
    )
endif()

if(GG_GFX_VULKAN_SUPPORT)
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
    PRIVATE
        $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
)

if(GG_GFX_OPENGL_SUPPORT)
    target_compile_definitions(
        gg.gfx
        PUBLIC
            GG_GFX_OPENGL_SUPPORT
    )
endif()

if(GG_GFX_VULKAN_SUPPORT)
    target_compile_definitions(
        gg.gfx
        PUBLIC
            GG_GFX_VULKAN_SUPPORT
    )
endif()

# compile options
target_compile_options(
    gg.gfx
    PRIVATE
        $<$<STREQUAL:${COMPILER},gnu>:-fno-exceptions>
        $<$<STREQUAL:${COMPILER},gnu>:-Wall>
        $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
        $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
        $<$<STREQUAL:${COMPILER},gnu>:-Werror>
        #$<$<STREQUAL:${COMPILER},msvc>:/EHs-c->
        $<$<STREQUAL:${COMPILER},msvc>:/W4>
        $<$<STREQUAL:${COMPILER},msvc>:/WX>
)

# link libraries
target_link_libraries(
    gg.gfx
    PUBLIC
        gg.app
)

if(GG_GFX_OPENGL_SUPPORT)
    target_link_libraries(
        gg.gfx
        PRIVATE
            ${OPENGL_LIBRARIES}
            gg.glew
    )
endif()

if(GG_GFX_VULKAN_SUPPORT)
    target_link_libraries(
        gg.gfx
        PRIVATE
            ${Vulkan_LIBRARIES}
    )
endif()

# group folder
set_target_properties(gg.gfx PROPERTIES FOLDER gg.libs)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.gfx.test ${TEST_FILES})

    # include directories
    target_include_directories(
        gg.gfx.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile definitions
    target_compile_definitions(
        gg.gfx.test
         PRIVATE
            $<$<STREQUAL:${COMPILER},msvc>:_CRT_SECURE_NO_WARNINGS>
    )

    # compile options
    target_compile_options(
        gg.gfx.test
        PRIVATE
            $<$<STREQUAL:${COMPILER},gnu>:-fexceptions>
            $<$<STREQUAL:${COMPILER},gnu>:-Wall>
            $<$<STREQUAL:${COMPILER},gnu>:-Werror>
            $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
            $<$<STREQUAL:${COMPILER},gnu>:-Wno-format-security>
            $<$<STREQUAL:${COMPILER},gnu>:-Wno-nonnull>
            $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
            $<$<STREQUAL:${COMPILER},msvc>:/EHsc>
            $<$<STREQUAL:${COMPILER},msvc>:/W4>
            $<$<STREQUAL:${COMPILER},msvc>:/WX>
    )

    # link libraries
    target_link_libraries(gg.gfx.test gg.test gg.gfx)

    # group folder
    set_target_properties(gg.gfx.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    catch_discover_tests(gg.gfx.test)
endif()
