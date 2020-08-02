# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGThreads)
include(GGSrcFiles.cmake)

# library
add_library(
    gg.core
    STATIC
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile features
target_compile_features(
    gg.core
    PUBLIC
        cxx_std_17
)

# compile definitions
target_compile_definitions(
    gg.core
    PUBLIC
        GG_CORE
        $<$<CONFIG:debug>:GG_DEBUG>
        $<$<CONFIG:release>:GG_DEBUG>
        $<$<STREQUAL:${compiler},gnu>:GG_GNU>
        $<$<STREQUAL:${compiler},msvc>:GG_MSVC>
        $<$<STREQUAL:${compiler},msvc>:_CRT_SECURE_NO_WARNINGS>
        $<$<STREQUAL:${platform},android>:GG_ANDROID>
        $<$<STREQUAL:${platform},mac>:GG_MAC>
        $<$<STREQUAL:${platform},linux>:GG_LINUX>
        $<$<STREQUAL:${platform},windows>:GG_WINDOWS>
        $<$<STREQUAL:${platform},windows>:NOMINMAX>
        $<$<STREQUAL:${platform},uwp>:GG_UWP>
        $<$<STREQUAL:${platform_architecture},x86>:GG_X86>
        $<$<STREQUAL:${platform_architecture},x86_64>:GG_X86_64>
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.core
    PUBLIC
        $<$<STREQUAL:${compiler},gnu>:$<$<CONFIG:debug>:-g>>
        $<$<STREQUAL:${compiler},gnu>:$<$<CONFIG:debug>:-O0>>
        $<$<STREQUAL:${compiler},gnu>:$<$<CONFIG:release>:-s>>
        $<$<STREQUAL:${compiler},gnu>:$<$<CONFIG:release>:-O3>>
        $<$<STREQUAL:${compiler},gnu>:$<$<CONFIG:distribution>:-s>>
        $<$<STREQUAL:${compiler},gnu>:$<$<CONFIG:distribution>:-O3>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:debug>:/MDd>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:debug>:/Ob0>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:debug>:/Od>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:release>:/MD>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:release>:/Ob2>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:release>:/Ox>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:distribution>:/MD>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:distribution>:/Ob2>>
        $<$<STREQUAL:${compiler},msvc>:$<$<CONFIG:distribution>:/Ox>>
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
target_link_libraries(gg.core Threads::Threads)

# group folder
set_target_properties(gg.core PROPERTIES FOLDER gg.libs)

# testing
if(GGLIBS_ENABLE_TESTING)
    # executable
    add_executable(gg.core.test ${test_files})

    # include directories
    target_include_directories(
        gg.core.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.core.test
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
    target_link_libraries(gg.core.test gg.test gg.core)

    # group folder
    set_target_properties(gg.core.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    ParseAndAddCatchTests(gg.core.test)
endif()
