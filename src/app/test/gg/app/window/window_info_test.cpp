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
        REQUIRE(type::is_copy_assignable<window_info>::value);
        REQUIRE(!type::is_trivially_assignable<window_info>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<window_info>::value);
        REQUIRE(!type::is_trivially_constructible<window_info>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<window_info>::value);
        REQUIRE(!type::is_trivially_copy_constructible<window_info>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<window_info>::value);
        REQUIRE(type::is_trivially_destructible<window_info>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<window_info>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<window_info>::value);
    }
}

//==============================================================================
}
//==============================================================================
