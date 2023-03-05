//==============================================================================
#if defined(GG_GFX_VULKAN_SUPPORT)
//==============================================================================

#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/type_trait.h"
#include "gg/gfx/vulkan/vulkan_context.h"

//==============================================================================
namespace gg::gfx::vulkan_context_test
{
//==============================================================================

TEST_CASE("vulkan_context_test", "[gg.gfx.vulkan_context]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<vulkan_context>::value);
        REQUIRE(!type::is_trivially_assignable<vulkan_context>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<vulkan_context>::value);
        REQUIRE(!type::is_trivially_constructible<vulkan_context>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<vulkan_context>::value);
        REQUIRE(!type::is_trivially_copy_constructible<vulkan_context>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<vulkan_context>::value);
        REQUIRE(!type::is_trivially_destructible<vulkan_context>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<vulkan_context>::value);
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
