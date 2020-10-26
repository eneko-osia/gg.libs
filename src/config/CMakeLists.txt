# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.config
    STATIC
        ${include_files}
        ${src_files}
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
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.config
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
target_link_libraries(gg.config gg.core)

# group folder
set_target_properties(gg.config PROPERTIES FOLDER gg.libs)

# testing
if(GGLIBS_ENABLE_TESTING)
    # executable
    add_executable(gg.config.test ${test_files})

    # include directories
    target_include_directories(
        gg.config.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.config.test
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
    target_link_libraries(gg.config.test gg.test gg.config)

    # group folder
    set_target_properties(gg.config.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    ParseAndAddCatchTests(gg.config.test)
endif()
