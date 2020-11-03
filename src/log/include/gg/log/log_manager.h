#ifndef _gg_log_log_manager_h_
#define	_gg_log_log_manager_h_

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"
#include "gg/core/pattern/singleton/singleton_automatic.h"
#include "gg/core/string/type/string_static.h"
#include "gg/core/thread/thread.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/utils/time.h"
#include "gg/log/channel/channel.h"

namespace gg::log
{
    class handler;

    class log_manager final : public singleton_automatic<log_manager>
    {
    public:

        // methods

        template <typename CHANNEL, typename... ARGS>
        void add_channel(ARGS &&... args) noexcept
        {
            GG_ASSERT(!has_channel<CHANNEL>());
            m_channels.emplace_back(CHANNEL::get_id(), type::forward<ARGS>(args)...);
        }

        template <typename CHANNEL>
        void remove_channel(void) noexcept
        {
            m_channels.erase(
                container::find_if(
                    m_channels.begin(),
                    m_channels.end(),
                    [] (channel const & rhs)
                    {
                        return CHANNEL::get_id() == rhs.get_id();
                    }));
        }

        template <typename CHANNEL>
        void set_channel(flags flags, level level, bool8 enabled) noexcept
        {
            channel * channel = get_channel<CHANNEL>();
            GG_RETURN_IF(!channel);

            channel->set_flags(flags);
            channel->set_level(level);
            channel->is_enabled(enabled);
        }

        void add_handler(handler * handler) noexcept;
        void remove_handler(handler const * handler) noexcept;

        template <typename CHANNEL, typename... ARGS>
        void log(level level, string_ref const & message, ARGS &&... args) noexcept
        {
            channel const * channel = get_channel<CHANNEL>();
            GG_RETURN_IF(!channel || !channel->is_enabled() || !channel->has_level(level));

            static size_type const k_max_size = 4096;
            string_static<k_max_size> buffer;

            if (channel->has_flag(flags::time))
            {
                millisecond time = time::system_now<millisecond>();

                {
                    size_type const size = buffer.size();
                    size_type const max_size = buffer.max_size() - size - 1;

                    time::format(
                        buffer.c_str() + size,
                        max_size,
                        "[%d/%m/%Y %H:%M:%S",
                        time);
                }

                {
                    size_type const size = buffer.size();
                    size_type const max_size = buffer.max_size() - size - 1;

                    string::format(
                        buffer.c_str() + size,
                        max_size,
                        ".%03d] ",
                        (time - second(time)).get());
                }
            }

            if (channel->has_flag(flags::thread))
            {
                size_type const size = buffer.size();
                size_type const max_size = buffer.max_size() - size - 1;

                string::format(
                    buffer.c_str() + size,
                    max_size,
                    "[%llu] ",
                    thread::current::get_id());
            }

            if (channel->has_flag(flags::channel))
            {
                size_type const size = buffer.size();
                size_type const max_size = buffer.max_size() - size - 1;

                string::format(
                    buffer.c_str() + size,
                    max_size,
                    "[%s] ",
                    CHANNEL::get_name().c_str());
            }

            if (channel->has_flag(flags::level))
            {
                size_type const size = buffer.size();
                size_type const max_size = buffer.max_size() - size - 1;

                string::format(
                    buffer.c_str() + size,
                    max_size,
                    "[%s] ",
                    level_descriptors[enums::cast(level)]);
            }

            size_type const size = buffer.size();
            size_type const max_size = buffer.max_size() - size - 1;

            string::format(
                buffer.c_str() + size,
                max_size,
                message.c_str(),
                type::forward<ARGS>(args)...);

            log(level, buffer);
        }

        void log(level level, string_ref const & message) noexcept;

        // inquiry

        template <typename CHANNEL>
        bool8 has_channel(void) const noexcept
        {
            return nullptr != get_channel<CHANNEL>();
        }

        bool8 has_handler(handler const * handler) const noexcept;

    private:

        // constructors

        log_manager(void) noexcept = default;
        ~log_manager(void) noexcept = default;

        // friendships

        friend class gg::memory;

        // type definitions

        typedef array_dynamic<channel> channel_container;
        typedef array_dynamic<handler *> handler_container;

        // accesors

        template <typename CHANNEL>
        channel * get_channel(void) noexcept
        {
            auto it = container::find_if(
                m_channels.begin(),
                m_channels.end(),
                [] (channel const & rhs)
                {
                    return CHANNEL::get_id() == rhs.get_id();
                });
            return it == m_channels.end() ? nullptr : &(*it);
        }

        template <typename CHANNEL>
        channel const * get_channel(void) const noexcept
        {
            auto it = container::find_if(
                m_channels.begin(),
                m_channels.end(),
                [] (channel const & rhs)
                {
                    return CHANNEL::get_id() == rhs.get_id();
                });
            return it == m_channels.end() ? nullptr : &(*it);
        }

    private:

        // attributes

        channel_container m_channels;
        handler_container m_handlers;
    };
}

#endif // _gg_log_log_manager_h_
