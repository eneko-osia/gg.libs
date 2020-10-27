#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_dynamic.h"
#include "gg/log/channel/channel_helper.h"
#include "gg/log/handler.h"
#include "gg/log/logger.h"

//==============================================================================

GG_LOG_CHANNEL_DEFINE(mock_channel)

//==============================================================================
namespace gg::log::logger_test
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

TEST_CASE("logger.level", "[gg.log]")
{
    SECTION("level descriptors")
    {
        REQUIRE(
            string_ref(GG_TEXT("error")) ==
            level_descriptors[enums::cast(level::error)]);

        REQUIRE(
            string_ref(GG_TEXT("warning")) ==
            level_descriptors[enums::cast(level::warning)]);

        REQUIRE(
            string_ref(GG_TEXT("normal")) ==
            level_descriptors[enums::cast(level::normal)]);

        REQUIRE(
            string_ref(GG_TEXT("debug")) ==
            level_descriptors[enums::cast(level::debug)]);

        REQUIRE(
            string_ref(GG_TEXT("verbose")) ==
            level_descriptors[enums::cast(level::verbose)]);
    }
}

TEST_CASE("logger.error", "[gg.log]")
{
    mock_handler handler;
    log_manager::get_instance().add_handler(&handler);

    SECTION("error")
    {
        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            bit_field::add(flags::channel, flags::level),
            level::error,
            true);
        logger::error<mock_channel>(GG_TEXT("message"));

        REQUIRE(handler.m_level == level::error);
        REQUIRE(handler.m_message == GG_TEXT("[mock_channel] [error] message"));
    }

    log_manager::get_instance().remove_handler(&handler);
}

TEST_CASE("logger.warning", "[gg.log]")
{
    mock_handler handler;
    log_manager::get_instance().add_handler(&handler);

    SECTION("warning")
    {
        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            bit_field::add(flags::channel, flags::level),
            level::warning,
            true);
        logger::warning<mock_channel>(GG_TEXT("message"));

        REQUIRE(handler.m_level == level::warning);
        REQUIRE(handler.m_message == GG_TEXT("[mock_channel] [warning] message"));
    }

    log_manager::get_instance().remove_handler(&handler);
}

TEST_CASE("logger.normal", "[gg.log]")
{
    mock_handler handler;
    log_manager::get_instance().add_handler(&handler);

    SECTION("normal")
    {
        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            bit_field::add(flags::channel, flags::level),
            level::normal,
            true);
        logger::normal<mock_channel>(GG_TEXT("message"));

        REQUIRE(handler.m_level == level::normal);
        REQUIRE(handler.m_message == GG_TEXT("[mock_channel] [normal] message"));
    }

    log_manager::get_instance().remove_handler(&handler);
}

TEST_CASE("logger.debug", "[gg.log]")
{
    mock_handler handler;
    log_manager::get_instance().add_handler(&handler);

    SECTION("debug")
    {
        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            bit_field::add(flags::channel, flags::level),
            level::debug,
            true);
        logger::debug<mock_channel>(GG_TEXT("message"));

#if defined(GG_DEBUG)
        REQUIRE(handler.m_level == level::debug);
        REQUIRE(handler.m_message == GG_TEXT("[mock_channel] [debug] message"));
#else
        REQUIRE(handler.m_level == level::max);
        REQUIRE(handler.m_message == GG_TEXT(""));
#endif
    }

    log_manager::get_instance().remove_handler(&handler);
}

TEST_CASE("logger.verbose", "[gg.log]")
{
    mock_handler handler;
    log_manager::get_instance().add_handler(&handler);

    SECTION("verbose")
    {
        GG_LOG_CHANNEL_CREATE(
            mock_channel,
            bit_field::add(flags::channel, flags::level),
            level::verbose,
            true);
        logger::verbose<mock_channel>(GG_TEXT("message"));

#if defined(GG_DEBUG)
        REQUIRE(handler.m_level == level::verbose);
        REQUIRE(handler.m_message == GG_TEXT("[mock_channel] [verbose] message"));
#else
        REQUIRE(handler.m_level == level::max);
        REQUIRE(handler.m_message == GG_TEXT(""));
#endif
    }

    log_manager::get_instance().remove_handler(&handler);
}

//==============================================================================
}
//==============================================================================
