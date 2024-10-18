# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.config
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.config
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.config
    PUBLIC
        GG_CONFIG
    PRIVATE
        $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.config
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
target_link_libraries(gg.config gg.core)

# group folder
set_target_properties(gg.config PROPERTIES FOLDER gg.libs)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.config.test ${TEST_FILES})

    # include directories
    target_include_directories(
        gg.config.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile definitions
    target_compile_definitions(
        gg.config.test
         PRIVATE
            $<$<STREQUAL:${COMPILER},msvc>:_CRT_SECURE_NO_WARNINGS>
            $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
    )

    # compile options
    target_compile_options(
        gg.config.test
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
    target_link_libraries(gg.config.test gg.test gg.config)

    # group folder
    set_target_properties(gg.config.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    catch_discover_tests(gg.config.test)
endif()
