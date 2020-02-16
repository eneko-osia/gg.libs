#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory_buffer_static.h"

//==============================================================================
namespace gg::memory_buffer_static_test
{
//==============================================================================

static constexpr uint32 k_bytes = 32;
typedef memory_buffer_static<k_bytes> mock_memory_buffer_static;

//==============================================================================

TEST_CASE("memory_buffer_static", "[gg.memory_buffer_static]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(mock_memory_buffer_static) == k_bytes);
    }

    SECTION("constructible")
    {
        REQUIRE(type::is_constructible<mock_memory_buffer_static>::value);
        REQUIRE(type::no_constructor<mock_memory_buffer_static>::value);
    }

    SECTION("destructible")
    {
        REQUIRE(type::is_destructible<mock_memory_buffer_static>::value);
        REQUIRE(type::no_destructor<mock_memory_buffer_static>::value);
    }

    SECTION("copyable")
    {
        REQUIRE(!type::is_copyable<mock_memory_buffer_static>::value);
        REQUIRE(!type::no_copy_constructor<mock_memory_buffer_static>::value);
    }

    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<mock_memory_buffer_static>::value);
    }

    SECTION("comparable")
    {
        REQUIRE(type::no_equality_operator<mock_memory_buffer_static>::value);
    }

    SECTION("pod")
    {
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<mock_memory_buffer_static>::value);
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<mock_memory_buffer_static>::value);
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_memory_buffer_static>::value);
    }
}

TEST_CASE("memory_buffer_static.constructor", "[gg.memory_buffer_static]")
{
    SECTION("memory_buffer_static")
    {
        mock_memory_buffer_static buffer;
        REQUIRE(buffer.data() != nullptr);
        REQUIRE(buffer.size() == k_bytes);
    }
}

TEST_CASE("memory_buffer_static.get", "[gg.memory_buffer_static]")
{
    SECTION("get")
    {
        mock_memory_buffer_static buffer;
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
