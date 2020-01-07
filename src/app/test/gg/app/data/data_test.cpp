#include "gg/test/catch.h"

//==============================================================================

#include "gg/app/data/data.h"

//==============================================================================
namespace gg
{
//==============================================================================

TEST_CASE("data", "[gg.app.data]")
{
    SECTION("polymorphic")
    {
        REQUIRE_FALSE(type::is_polymorphic<data>());
    }

    SECTION("sizeof")
    {
        uint32 data_size = 0;

#if defined(GG_LINUX)
    #if defined(GG_X86)
        data_size = 12;
    #elif defined(GG_X86_64)
        data_size = 24;
    #endif
#elif defined(GG_WINDOWS)
    #if defined(GG_X86)
        data_size = 16;
    #elif defined(GG_X86_64)
        data_size = 32;
    #endif
#endif

        REQUIRE(sizeof(data) == data_size);
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
