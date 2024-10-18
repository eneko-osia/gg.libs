# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# options
option(
    GG_APP_WINDOW_SUPPORT
    "app window support"
    OFF
)

# includes
if(GG_APP_WINDOW_SUPPORT)
    include(GGX11)
endif()

include(GGSrcFiles.cmake)

# library
add_library(
    gg.app
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.app
    PUBLIC
        GG_APP
    PRIVATE
        $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
)

if(GG_APP_WINDOW_SUPPORT)
    target_compile_definitions(
        gg.app
        PUBLIC
            GG_APP_WINDOW_SUPPORT
    )
endif()

# compile options
target_compile_options(
    gg.app
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
target_link_libraries(gg.app gg.core)

if(GG_APP_WINDOW_SUPPORT)
    target_link_libraries(gg.app ${X11_LIBRARIES})
endif()

# group folder
set_target_properties(gg.app PROPERTIES FOLDER gg.libs)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.app.test ${TEST_FILES})

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
    target_link_libraries(gg.app.test gg.test gg.app)

    # group folder
    set_target_properties(gg.app.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    catch_discover_tests(gg.app.test)
endif()
