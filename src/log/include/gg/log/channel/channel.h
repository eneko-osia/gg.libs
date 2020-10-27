#ifndef _gg_log_channel_h_
#define _gg_log_channel_h_

#include "gg/core/hash/hash.h"
#include "gg/core/pattern/identifiable.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/utils/bit_field.h"
#include "gg/log/logger_defs.h"

namespace gg::log
{
    class channel : public identifiable<uint32>
    {
    public:

        // constructors

        channel(uint32 id, flags flags, level level, bool8 enabled) noexcept
            : identifiable<uint32>(id)
            , m_flags(flags)
            , m_level(level)
            , m_enabled(enabled)
        {
        }
        ~channel(void) noexcept = default;

        // accessors

        void set_flags(flags flags) noexcept
        {
            m_flags = flags;
        }

        void set_level(level level) noexcept
        {
            m_level = level;
        }

        // inquiry

        bool8 has_flag(flags flags) const noexcept
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

    private:

        // attributes

        flags m_flags;
        level m_level;
        bool8 m_enabled;
    };

    // macros

    #define GG_LOG_CHANNEL_DEFINE(CHANNEL)                      \
        namespace gg::log                                       \
        {                                                       \
            class CHANNEL final                                 \
            {                                                   \
            public:                                             \
                static uint32 get_id(void) noexcept             \
                {                                               \
                    static uint32 const channel_id =            \
                        gg::hash::fnv1::generate(get_name());   \
                    return channel_id;                          \
                }                                               \
                static gg::string_ref get_name(void) noexcept   \
                {                                               \
                    return GG_TEXT(#CHANNEL);                   \
                }                                               \
            private:                                            \
                CHANNEL(void) noexcept = default;               \
                ~CHANNEL(void) noexcept = default;              \
            };                                                  \
        }
}

#endif // _gg_log_channel_h_
