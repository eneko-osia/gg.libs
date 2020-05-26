# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGX11)
include(GGSrcFiles.cmake)

# library
add_library(
    gg.app
    STATIC
        ${deps_files}
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.app
    PUBLIC
        GG_APP
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_CRT_SECURE_NO_WARNINGS>
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.app
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
target_link_libraries(gg.app ${X11_LIBRARIES} gg.core)

# group folder
set_target_properties(gg.app PROPERTIES FOLDER gg.libs)

# testing
if(GGLIBS_ENABLE_TESTING)
    # executable
    add_executable(gg.app.test ${test_files})

    # include directories
    target_include_directories(
        gg.app.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.app.test
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
    target_link_libraries(gg.app.test gg.test gg.app)

    # group folder
    set_target_properties(gg.app.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    ParseAndAddCatchTests(gg.app.test)
endif()
