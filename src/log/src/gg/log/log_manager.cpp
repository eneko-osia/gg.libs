#include "gg/log/log_manager.h"

//==============================================================================

#include "gg/core/container/container.h"

//==============================================================================
namespace gg::log
{
//==============================================================================

void log_manager::add_handler(ilog_handler * handler) noexcept
{
    m_handlers.emplace_back(handler);
}

bool8 log_manager::has_handler(ilog_handler const * handler) const noexcept
{
    auto cit =
        container::find_if(
            m_handlers.begin(),
            m_handlers.end(),
            [&] (ilog_handler const * log_handler)
            {
                return log_handler == handler;
            });
    return cit != m_handlers.end();
}

void log_manager::log(level level, string_ref const & message) noexcept
{
    container::for_each(
        m_handlers.begin(),
        m_handlers.end(),
        [&] (ilog_handler * log_handler)
        {
            log_handler->log(level, message);
        });
}

void log_manager::remove_handler(ilog_handler const * handler) noexcept
{
    m_handlers.erase(
        container::remove_if(
            m_handlers.begin(),
            m_handlers.end(),
            [&] (ilog_handler const * log_handler)
            {
                return log_handler == handler;
            }));
}

//==============================================================================
}
//==============================================================================
