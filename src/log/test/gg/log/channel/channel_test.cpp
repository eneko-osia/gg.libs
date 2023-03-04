#include "gg/test/catch.h"

//==============================================================================

#include "gg/log/channel/channel_helper.h"
#include "gg/log/channel/channel.h"

//==============================================================================

GG_LOG_CHANNEL_DEFINE(mock_channel)

//==============================================================================
namespace gg::log::channel_test
{
//==============================================================================

TEST_CASE("channel", "[gg.log]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<mock_channel>::value);
        REQUIRE(type::has_trivial_assign<mock_channel>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<mock_channel>::value);
        REQUIRE(!type::has_trivial_constructor<mock_channel>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copyable<mock_channel>::value);
        REQUIRE(!type::has_trivial_copy<mock_channel>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<mock_channel>::value);
        REQUIRE(!type::has_trivial_destructor<mock_channel>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<mock_channel>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_channel>::value);
    }
}

TEST_CASE("channel.create", "[gg.log]")
{
    SECTION("create")
    {
        log_manager const & manager = log_manager::get_instance();
        REQUIRE(!manager.has_channel<mock_channel>());

        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            flags::channel,
            level::normal,
            false);
        REQUIRE(manager.has_channel<mock_channel>());

        GG_LOG_CHANNEL_DESTROY(mock_channel);
        REQUIRE(!manager.has_channel<mock_channel>());
    }
}

//==============================================================================
}
//==============================================================================
