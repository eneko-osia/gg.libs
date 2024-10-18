//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/test/catch.h"

//==============================================================================

#include "gg/gfx/opengl/context/opengl_context.h"

//==============================================================================
namespace gg::gfx::opengl::context_test
{
//==============================================================================

TEST_CASE("opengl_context_test", "[gg.gfx.opengl_context]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<context>::value);
        REQUIRE(type::is_trivially_assignable<context>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<context>::value);
        REQUIRE(!type::is_trivially_constructible<context>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<context>::value);
        REQUIRE(!type::is_trivially_copy_constructible<context>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<context>::value);
        REQUIRE(!type::is_trivially_destructible<context>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<context>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<context>::value);
    }
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
