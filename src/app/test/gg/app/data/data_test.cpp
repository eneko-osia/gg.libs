#include "gg/test/catch.h"

//==============================================================================

#include "gg/app/data/data.h"

//==============================================================================
namespace gg
{
//==============================================================================

TEST_CASE("data", "[gg.app.data]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<data>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<data>::value);
        REQUIRE(!type::has_trivial_constructor<data>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copyable<data>::value);
        REQUIRE(!type::has_trivial_copy<data>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<data>::value);
        REQUIRE(!type::has_trivial_destructor<data>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<data>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<data>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<data>::value);
    }
}

TEST_CASE("data::add_argument", "[gg.app.data]")
{
    SECTION("add_argument")
    {
        data app_data;
        app_data.add_argument(string_ref("argument_1"));
        REQUIRE(app_data.get_arguments().front() == "argument_1");
    }
}

//==============================================================================

TEST_CASE("data::set_hinstance", "[gg.app.data]")
{
    #if defined(GG_WINDOWS)
    SECTION("set_hinstance")
    {
        data app_data;

        HINSTANCE hinstance = (HINSTANCE) GetModuleHandle(NULL);
        app_data.set_hinstance(hinstance);
        REQUIRE(app_data.get_hinstance() == hinstance);
    }
    #endif
}

//==============================================================================
}
//==============================================================================
