# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGThreads)
include(GGSrcFiles.cmake)

# library
add_library(
    gg.core
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.core
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
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
        $<$<CONFIG:release_with_debug>:GG_DEBUG>
        $<$<STREQUAL:${COMPILER},gnu>:GG_GNU>
        $<$<STREQUAL:${COMPILER},msvc>:GG_MSVC>
        $<$<STREQUAL:${SYSTEM},android>:GG_ANDROID>
        $<$<STREQUAL:${SYSTEM},linux>:GG_LINUX>
        $<$<STREQUAL:${SYSTEM},mac>:GG_MAC>
        $<$<STREQUAL:${SYSTEM},uwp>:GG_UWP>
        $<$<STREQUAL:${SYSTEM},windows>:GG_WINDOWS>
        $<$<STREQUAL:${SYSTEM_ARCHITECTURE},x86>:GG_X86>
        $<$<STREQUAL:${SYSTEM_ARCHITECTURE},x86_64>:GG_X86_64>
    PRIVATE
        $<$<STREQUAL:${COMPILER},msvc>:_CRT_SECURE_NO_WARNINGS>
        $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
        $<$<STREQUAL:${SYSTEM},windows>:NOMINMAX>
)

# compile options
target_compile_options(
    gg.core
    PUBLIC
        $<$<STREQUAL:${COMPILER},gnu>:$<$<CONFIG:debug>:-g>>
        $<$<STREQUAL:${COMPILER},gnu>:$<$<CONFIG:debug>:-O0>>
        $<$<STREQUAL:${COMPILER},gnu>:$<$<CONFIG:release_with_debug>:-s>>
        $<$<STREQUAL:${COMPILER},gnu>:$<$<CONFIG:release_with_debug>:-O3>>
        $<$<STREQUAL:${COMPILER},gnu>:$<$<CONFIG:release>:-s>>
        $<$<STREQUAL:${COMPILER},gnu>:$<$<CONFIG:release>:-O3>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:debug>:/MDd>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:debug>:/Ob0>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:debug>:/Od>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:release_with_debug>:/MDd>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:release_with_debug>:/Ob2>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:release_with_debug>:/Ox>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:release>:/MD>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:release>:/Ob2>>
        $<$<STREQUAL:${COMPILER},msvc>:$<$<CONFIG:release>:/Ox>>
    PRIVATE
        $<$<STREQUAL:${COMPILER},gnu>:-fno-exceptions>
        $<$<STREQUAL:${COMPILER},gnu>:-Wall>
        $<$<STREQUAL:${COMPILER},gnu>:-Werror>
        $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
        $<$<STREQUAL:${COMPILER},gnu>:-Wno-format-security>
        $<$<STREQUAL:${COMPILER},gnu>:-Wno-nonnull>
        $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
        # $<$<STREQUAL:${COMPILER},msvc>:/EHs-c->
        $<$<STREQUAL:${COMPILER},msvc>:/W4>
        $<$<STREQUAL:${COMPILER},msvc>:/WX>
)

# link libraries
target_link_libraries(gg.core Threads::Threads ${CMAKE_DL_LIBS})

# group folder
set_target_properties(gg.core PROPERTIES FOLDER gg.libs)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.core.test ${TEST_FILES})

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
    target_link_libraries(gg.core.test gg.test gg.core)

    # group folder
    set_target_properties(gg.core.test PROPERTIES FOLDER gg.libs.test)

    # parse tests
    catch_discover_tests(gg.core.test)
endif()
