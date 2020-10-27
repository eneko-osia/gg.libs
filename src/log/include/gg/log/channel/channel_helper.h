#ifndef _gg_log_channel_helper_h_
#define _gg_log_channel_helper_h_

#include "gg/log/channel/channel.h"
#include "gg/log/log_manager.h"

namespace gg::log
{
    template <typename CHANNEL>
    class channel_add_helper final
    {
    public:
        channel_add_helper(flags flags, level level, bool8 enabled) noexcept
        {
            log_manager::get_instance().add_channel<CHANNEL>(flags, level, enabled);
        }
    };

    template <typename CHANNEL>
    class channel_destroy_helper final
    {
    public:
        channel_destroy_helper(void) noexcept
        {
            log_manager::get_instance().remove_channel<CHANNEL>();
        }
    };

    // macros

    #define GG_LOG_CHANNEL_CREATE(CHANNEL, FLAGS, LEVEL, ENABLED)       \
        gg::log::channel_add_helper<gg::log::CHANNEL>                   \
            CHANNEL##_add_helper(FLAGS, LEVEL, ENABLED)

    #define GG_LOG_CHANNEL_DESTROY(CHANNEL)                             \
        gg::log::channel_destroy_helper<gg::log::CHANNEL>               \
            CHANNEL##_destroy_helper
}

#endif // _gg_log_channel_helper_h_
