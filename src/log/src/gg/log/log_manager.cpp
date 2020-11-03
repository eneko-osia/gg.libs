#include "gg/log/log_manager.h"

//==============================================================================

#include "gg/log/handler.h"

//==============================================================================
namespace gg::log
{
//==============================================================================

void log_manager::add_handler(handler * handler) noexcept
{
    GG_ASSERT(!has_handler(handler));
    m_handlers.emplace_back(handler);
}

bool8 log_manager::has_handler(handler const * handler) const noexcept
{
    auto cit =
        container::find_if(
            m_handlers.begin(),
            m_handlers.end(),
            [&] (auto const * rhs)
            {
                return handler == rhs;
            });
    return cit != m_handlers.end();
}

void log_manager::log(level level, string_ref const & message) noexcept
{
    container::for_each(
        m_handlers.begin(),
        m_handlers.end(),
        [&] (auto * handler)
        {
            handler->log(level, message);
        });
}

void log_manager::remove_handler(handler const * handler) noexcept
{
    m_handlers.erase(
        container::find_if(
            m_handlers.begin(),
            m_handlers.end(),
            [&] (auto const * rhs)
            {
                return handler == rhs;
            }));
}

//==============================================================================
}
//==============================================================================
