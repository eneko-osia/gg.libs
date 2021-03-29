//==============================================================================

#include "gg/test/catch.h"

//==============================================================================

#include "gg/app/window/window_info.h"

//==============================================================================
namespace gg::app::window_info_test
{
//==============================================================================

TEST_CASE("window_info", "[gg.app.window_info]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<window_info>::value);
        REQUIRE(!type::has_trivial_assign<window_info>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<window_info>::value);
        REQUIRE(!type::has_trivial_constructor<window_info>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<window_info>::value);
        REQUIRE(!type::has_trivial_copy<window_info>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<window_info>::value);
        REQUIRE(type::has_trivial_destructor<window_info>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<window_info>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<window_info>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<window_info>::value);
    }
}

//==============================================================================
}
//==============================================================================
