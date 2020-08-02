#ifndef _gg_log_channel_h_
#define    _gg_log_channel_h_

#include "gg/core/pattern/singleton/singleton_manual.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/utils/bit_field.h"
#include "gg/log/channel/channel_helper.h"

namespace gg::log
{
    template <typename CHANNEL>
    class channel : public singleton_manual<CHANNEL>
    {
    public:

        // methods

        void set_flags(channel_flags flags) noexcept
        {
            m_flags = flags;
        }

        void set_level(level level) noexcept
        {
            m_level = level;
        }

        // inquiry

        bool8 has_flag(channel_flags flags) const noexcept
        {
            return bit_field::is_set(m_flags, flags);
        }

        bool8 has_level(level level) const noexcept
        {
            return level <= m_level;
        }

        bool8 is_enabled(void) const noexcept
        {
            return m_enabled;
        }

        void is_enabled(bool8 enabled) noexcept
        {
            m_enabled = enabled;
        }

    protected:

        // constructors

        channel(void) noexcept :
            m_flags(channel_flags::full),
            m_level(level::verbose),
            m_enabled(true)
        {
        }
        ~channel(void) noexcept = default;

    private:

        // attributes

        channel_flags m_flags;
        level m_level;
        bool8 m_enabled;
    };

    // macros

    #define GG_LOG_CHANNEL_DEFINE(CHANNEL)                                  \
        class CHANNEL final : public channel<CHANNEL>                       \
        {                                                                   \
        public:                                                             \
            string_ref get_name(void) const noexcept                        \
            {                                                               \
                return GG_TEXT(#CHANNEL);                                   \
            }                                                               \
        protected:                                                          \
            friend class gg::memory;                                        \
            CHANNEL(void) noexcept = default;                               \
            ~CHANNEL(void) noexcept = default;                              \
        };

    #define GG_LOG_CHANNEL_CREATE(CHANNEL, LEVEL, FLAGS, ENABLED)           \
        channel_helper<CHANNEL> CHANNEL##_helper(LEVEL, FLAGS, ENABLED);
}

#endif // _gg_log_channel_h_
