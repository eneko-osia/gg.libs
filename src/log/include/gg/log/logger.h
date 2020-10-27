#ifndef _gg_log_logger_h_
#define	_gg_log_logger_h_

#include "gg/log/log_manager.h"

namespace gg::log
{
    class logger final
    {
    public:

        // methods

#if defined(GG_DEBUG)

        template <typename CHANNEL, typename... ARGS>
        static void debug(string_ref const & message, ARGS &&... args) noexcept
        {
            log<CHANNEL>(level::debug, message, type::forward<ARGS>(args)...);
        }

        template <typename CHANNEL, typename... ARGS>
        static void verbose(string_ref const & message, ARGS &&... args) noexcept
        {
            log<CHANNEL>(level::verbose, message, type::forward<ARGS>(args)...);
        }

#else

        template <typename CHANNEL, typename... ARGS>
        static void
        debug(
            string_ref const & GG_UNUSED_ARGUMENT(message),
            ARGS &&... GG_UNUSED_ARGUMENT(args)) noexcept
        {
        }

        template <typename CHANNEL, typename... ARGS>
        static void
        verbose(
            string_ref const & GG_UNUSED_ARGUMENT(message),
            ARGS &&... GG_UNUSED_ARGUMENT(args)) noexcept
        {
        }

#endif

        template <typename CHANNEL, typename... ARGS>
        static void error(string_ref const & message, ARGS &&... args) noexcept
        {
            log<CHANNEL>(level::error, message, type::forward<ARGS>(args)...);
        }

        template <typename CHANNEL, typename... ARGS>
        static void normal(string_ref const & message, ARGS &&... args) noexcept
        {
            log<CHANNEL>(level::normal, message, type::forward<ARGS>(args)...);
        }

        template <typename CHANNEL, typename... ARGS>
        static void warning(string_ref const & message, ARGS &&... args) noexcept
        {
            log<CHANNEL>(level::warning, message, type::forward<ARGS>(args)...);
        }

    private:

        // methods

        template <typename CHANNEL, typename... ARGS>
        static void log(level level, string_ref const & message, ARGS &&... args) noexcept
        {
            log_manager::get_instance().log<CHANNEL>(
                level,
                message,
                type::forward<ARGS>(args)...);
        }
    };
}

#endif // _gg_log_logger_h_
