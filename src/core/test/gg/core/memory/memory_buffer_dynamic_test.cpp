#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory_buffer_dynamic.h"

//==============================================================================
namespace gg::memory_buffer_dynamic_test
{
//==============================================================================

TEST_CASE("memory_buffer_dynamic", "[gg.memory_buffer_dynamic]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<memory_buffer_dynamic>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<memory_buffer_dynamic>::value);
        REQUIRE(!type::has_trivial_constructor<memory_buffer_dynamic>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copyable<memory_buffer_dynamic>::value);
        REQUIRE(!type::has_trivial_copy<memory_buffer_dynamic>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<memory_buffer_dynamic>::value);
        REQUIRE(!type::has_trivial_destructor<memory_buffer_dynamic>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<memory_buffer_dynamic>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<memory_buffer_dynamic>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<memory_buffer_dynamic>::value);
    }
}

TEST_CASE("memory_buffer_dynamic.constructor", "[gg.memory_buffer_dynamic]")
{
    SECTION("memory_buffer_dynamic")
    {
        memory_buffer_dynamic buffer;
        REQUIRE(buffer.data() == nullptr);
        REQUIRE(buffer.size() == 0);
    }

    SECTION("memory_buffer_dynamic(size)")
    {
        memory_buffer_dynamic buffer(16);
        REQUIRE(buffer.data() != nullptr);
        REQUIRE(buffer.size() == 16);
    }

    SECTION("memory_buffer_dynamic(rvalue_memory_buffer_dynamic)")
    {
        memory_buffer_dynamic moved_buffer(16);
        memory_buffer_dynamic buffer(type::move(moved_buffer));
        REQUIRE(buffer.data() != nullptr);
        REQUIRE(buffer.size() == 16);
        REQUIRE(moved_buffer.data() == nullptr);
        REQUIRE(moved_buffer.size() == 0);
    }
}

TEST_CASE("memory_buffer_dynamic.operator=", "[gg.memory_buffer_dynamic]")
{
    SECTION("memory_buffer_dynamic = rvalue_memory_buffer_dynamic")
    {
        memory_buffer_dynamic moved_buffer(16);
        memory_buffer_dynamic buffer;
        buffer = type::move(moved_buffer);
        REQUIRE(buffer.data() != nullptr);
        REQUIRE(buffer.size() == 16);
        REQUIRE(moved_buffer.data() == nullptr);
        REQUIRE(moved_buffer.size() == 0);
    }
}

TEST_CASE("memory_buffer_dynamic.get", "[gg.memory_buffer_dynamic]")
{
    SECTION("get")
    {
        memory_buffer_dynamic buffer(16);
        buffer.get(0) = 3;
        buffer.get(1) = 2;
        buffer.get(2) = 1;

        REQUIRE(buffer.get(0) == 3);
        REQUIRE(buffer.get(1) == 2);
        REQUIRE(buffer.get(2) == 1);

        REQUIRE(buffer.get(0) == buffer.data<byte>()[0]);
        REQUIRE(buffer.get(1) == buffer.data<byte>()[1]);
        REQUIRE(buffer.get(2) == buffer.data<byte>()[2]);
    }
}

//==============================================================================
}
//==============================================================================
