# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.crypt
    STATIC
        ${deps_files}
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.crypt
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.crypt
    PUBLIC
        GG_crypt
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.crypt
    PRIVATE
        $<$<STREQUAL:${compiler},gnu>:-fno-exceptions>
        $<$<STREQUAL:${compiler},gnu>:-Wall>
        $<$<STREQUAL:${compiler},gnu>:-Wextra>
        $<$<STREQUAL:${compiler},gnu>:-Wpedantic>
        #$<$<STREQUAL:${compiler},msvc>:/EHs-c->
        #$<$<STREQUAL:${compiler},msvc>:/W4>
        $<$<STREQUAL:${compiler},msvc>:/WX>
)

# link libraries
target_link_libraries(gg.crypt gg.core)

# group folder
set_target_properties(gg.crypt PROPERTIES FOLDER gg.libs)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.crypt.test ${test_files})

    # include directories
    target_include_directories(
        gg.crypt.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.crypt.test
        PRIVATE
            $<$<STREQUAL:${compiler},gnu>:-fexceptions>
            $<$<STREQUAL:${compiler},gnu>:-Wall>
            $<$<STREQUAL:${compiler},gnu>:-Wextra>
            $<$<STREQUAL:${compiler},gnu>:-Wpedantic>
            $<$<STREQUAL:${compiler},msvc>:/EHsc>
            #$<$<STREQUAL:${compiler},msvc>:/W4>
            $<$<STREQUAL:${compiler},msvc>:/WX>
    )

    # link libraries
    target_link_libraries(gg.crypt.test gg.test gg.crypt)

    # group folder
    set_target_properties(gg.crypt.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    ParseAndAddCatchTests(gg.crypt.test)
endif()
