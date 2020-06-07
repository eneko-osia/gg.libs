#include "gg/test/catch.h"

//==============================================================================

#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app::window_test
{
//==============================================================================

TEST_CASE("window", "[gg.app.window]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<window>::value);
        REQUIRE(!type::has_trivial_assign<window>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<window>::value);
        REQUIRE(!type::has_trivial_constructor<window>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<window>::value);
        REQUIRE(!type::has_trivial_copy<window>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<window>::value);
        REQUIRE(!type::has_trivial_destructor<window>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<window>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<window>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(type::is_polymorphic<window>::value);
    }
}

TEST_CASE("window::init", "[gg.app.window]")
{
    SECTION("init")
    {
        window_info info =
        {
            GG_TEXT("Test"),
            64,
            64
        };

#if defined(GG_WINDOWS)
        info.m_hinstance = (HINSTANCE) GetModuleHandle(NULL);
#endif

        window win;
        REQUIRE(win.init(&info));
        win.finalize();
    }
}

//==============================================================================
}
//==============================================================================
