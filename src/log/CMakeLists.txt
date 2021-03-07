# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.log
    STATIC
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.log
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.log
    PUBLIC
        GG_LOG
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.log
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
    gg.log
    PUBLIC
        gg.core
)

# group folder
set_target_properties(gg.log PROPERTIES FOLDER gg.libs)

# testing
if(GGLIBS_ENABLE_TESTING)
    # executable
    add_executable(gg.log.test ${test_files})

    # include directories
    target_include_directories(
        gg.log.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.log.test
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
    target_link_libraries(gg.log.test gg.test gg.log)

    # group folder
    set_target_properties(gg.log.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    catch_discover_tests(gg.log.test)
endif()
