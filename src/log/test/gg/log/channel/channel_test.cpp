#include "gg/test/catch.h"

//==============================================================================

#include "gg/log/channel/channel.h"

//==============================================================================
namespace gg::log::channel_test
{
//==============================================================================

GG_LOG_CHANNEL_DEFINE(mock_channel);

//==============================================================================

TEST_CASE("channel", "[gg.log]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<mock_channel>::value);
        REQUIRE(!type::has_trivial_assign<mock_channel>::value);
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

    SECTION("pod")
    {
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<mock_channel>::value);
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<mock_channel>::value);
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_channel>::value);
    }
}

TEST_CASE("channel.create", "[gg.log]")
{
    REQUIRE(!mock_channel::is_available());

    SECTION("create")
    {
        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            level::normal,
            channel_flags::channel,
            false);

        REQUIRE(mock_channel::get_instance().has_level(level::error));
        REQUIRE(mock_channel::get_instance().has_level(level::warning));
        REQUIRE(mock_channel::get_instance().has_level(level::normal));
        REQUIRE(!mock_channel::get_instance().has_level(level::debug));
        REQUIRE(!mock_channel::get_instance().has_level(level::verbose));

        REQUIRE(mock_channel::get_instance().has_flag(channel_flags::channel));
        REQUIRE(!mock_channel::get_instance().has_flag(channel_flags::level));
        REQUIRE(!mock_channel::get_instance().has_flag(channel_flags::time));

        REQUIRE(!mock_channel::get_instance().is_enabled());
    }

    REQUIRE(!mock_channel::is_available());
}

//==============================================================================
}
//==============================================================================
