//==============================================================================
#if defined(GG_GFX_VULKAN_SUPPORT)
//==============================================================================

#include "gg/test/catch.h"

//==============================================================================

#include "gg/gfx/vulkan/context/vulkan_context.h"

//==============================================================================
namespace gg::gfx::vulkan_context_test
{
//==============================================================================

TEST_CASE("vulkan_context_test", "[gg.gfx.vulkan_context]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<vulkan_context>::value);
        REQUIRE(!type::has_trivial_assign<vulkan_context>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<vulkan_context>::value);
        REQUIRE(!type::has_trivial_constructor<vulkan_context>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<vulkan_context>::value);
        REQUIRE(!type::has_trivial_copy<vulkan_context>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<vulkan_context>::value);
        REQUIRE(!type::has_trivial_destructor<vulkan_context>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<vulkan_context>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<vulkan_context>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(type::is_polymorphic<vulkan_context>::value);
    }
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
