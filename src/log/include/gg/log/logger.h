#ifndef _gg_log_logger_h_
#define	_gg_log_logger_h_

#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/utils/time_utils.h"
#include "gg/log/channel/channel_defs.h"
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
        static void debug(string_ref const & message, ARGS &&... args) noexcept
        {
            GG_UNUSED(message);
        }

        template <typename CHANNEL, typename... ARGS>
        static void verbose(string_ref const & message, ARGS &&... args) noexcept
        {
            GG_UNUSED(message);
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
            CHANNEL const & channel = CHANNEL::get_instance();
            if (channel.is_enabled() && channel.has_level(level))
            {
                static size_type const k_max_size = 4096;
                string_static<k_max_size> buffer;

                if (channel.has_flag(channel_flags::time))
                {
                    millisecond current_time =
                        time_utils::system_now<millisecond>();
                    {
                        size_type buffer_size = buffer.size();
                        size_type buffer_max_size = buffer.max_size() - buffer_size - 1;

                        time_utils::format(
                            buffer.c_str() + buffer_size,
                            buffer_max_size,
                            "[%d/%m/%Y %H:%M:%S",
                            current_time);
                    }

                    {
                        size_type buffer_size = buffer.size();
                        size_type buffer_max_size = buffer.max_size() - buffer_size - 1;

                        string::format(
                            buffer.c_str() + buffer_size,
                            buffer_max_size,
                            ".%03d] ",
                            (current_time - second(current_time)).get());
                    }
                }

                if (channel.has_flag(channel_flags::channel))
                {
                    size_type buffer_size = buffer.size();
                    size_type buffer_max_size = buffer.max_size() - buffer_size - 1;

                    string::format(
                        buffer.c_str() + buffer_size,
                        buffer_max_size,
                        "[%s] ",
                        channel.get_name().c_str());
                }

                if (channel.has_flag(channel_flags::level))
                {
                    size_type buffer_size = buffer.size();
                    size_type buffer_max_size = buffer.max_size() - buffer_size - 1;

                    string::format(
                        buffer.c_str() + buffer_size,
                        buffer_max_size,
                        "[%s] ",
                        level_descriptors[enums::cast(level)]);
                }

                size_type buffer_size = buffer.size();
                size_type buffer_max_size = buffer.max_size() - buffer_size - 1;

                string::format(
                    buffer.c_str() + buffer_size,
                    buffer_max_size,
                    message.c_str(),
                    type::forward<ARGS>(args)...);
                log_manager::get_instance().log(level, buffer);
            }
        }
    };
}

#endif // _gg_log_logger_h_
