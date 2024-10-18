# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# add dependencies
add_subdirectory("deps/imgui")

# library
add_library(
    gg.gui
    STATIC
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.gui
    PUBLIC
        GG_GUI
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.gui
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
    gg.gui
    PUBLIC
        gg.gfx
    PRIVATE
        gg.imgui
)

# group folder
set_target_properties(gg.gui PROPERTIES FOLDER gg.libs)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.gui.test ${test_files})

    # include directories
    target_include_directories(
        gg.gui.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.gui.test
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
    target_link_libraries(gg.gui.test gg.test gg.gui)

    # group folder
    set_target_properties(gg.gui.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    catch_discover_tests(gg.gui.test)
endif()
