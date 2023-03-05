#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_dynamic.h"
#include "gg/log/handler.h"
#include "gg/log/log_manager.h"

//==============================================================================
namespace gg::log::log_manager_test
{
//==============================================================================

class mock_handler : public handler
{
public:

    void log(level level, string_ref const & message) noexcept
    {
        m_level = level;
        m_message = message;
    }

    level m_level = level::max;
    string_dynamic m_message;
};

//==============================================================================

TEST_CASE("log_manager", "[gg.log]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<log_manager>::value);
        REQUIRE(!type::is_trivially_assignable<log_manager>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<log_manager>::value);
        REQUIRE(!type::is_trivially_constructible<log_manager>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<log_manager>::value);
        REQUIRE(!type::is_trivially_copy_constructible<log_manager>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<log_manager>::value);
        REQUIRE(!type::is_trivially_destructible<log_manager>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<log_manager>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<log_manager>::value);
    }
}

TEST_CASE("log_manager.add_handler", "[gg.log]")
{
    SECTION("add_handler")
    {
        mock_handler handler;
        REQUIRE(!log_manager::get_instance().has_handler(&handler));
        log_manager::get_instance().add_handler(&handler);
        REQUIRE(log_manager::get_instance().has_handler(&handler));
    }
}

TEST_CASE("log_manager.remove_handler", "[gg.log]")
{
    SECTION("remove_handler")
    {
        mock_handler handler;
        log_manager::get_instance().add_handler(&handler);
        REQUIRE(log_manager::get_instance().has_handler(&handler));
        log_manager::get_instance().remove_handler(&handler);
        REQUIRE(!log_manager::get_instance().has_handler(&handler));
    }
}

TEST_CASE("log_manager.log", "[gg.log]")
{
    SECTION("log")
    {
        mock_handler handler;
        log_manager::get_instance().add_handler(&handler);
        log_manager::get_instance().log(level::normal, GG_TEXT("message"));
        REQUIRE(handler.m_level == level::normal);
        REQUIRE(handler.m_message == GG_TEXT("message"));
    }
}

//==============================================================================
}
//==============================================================================
