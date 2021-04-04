//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/test/catch.h"

//==============================================================================

#include "gg/gfx/opengl/context/opengl_context.h"

//==============================================================================
namespace gg::gfx::opengl_context_test
{
//==============================================================================

TEST_CASE("opengl_context_test", "[gg.gfx.opengl_context]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<opengl_context>::value);
        REQUIRE(type::has_trivial_assign<opengl_context>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<opengl_context>::value);
        REQUIRE(!type::has_trivial_constructor<opengl_context>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<opengl_context>::value);
        REQUIRE(!type::has_trivial_copy<opengl_context>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<opengl_context>::value);
        REQUIRE(!type::has_trivial_destructor<opengl_context>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<opengl_context>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<opengl_context>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<opengl_context>::value);
    }
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
