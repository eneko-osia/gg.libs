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
        REQUIRE(type::is_assignable<context>::value);
        REQUIRE(type::has_trivial_assign<context>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<context>::value);
        REQUIRE(!type::has_trivial_constructor<context>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<context>::value);
        REQUIRE(!type::has_trivial_copy<context>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<context>::value);
        REQUIRE(!type::has_trivial_destructor<context>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<context>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<context>::value);
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
