#ifndef _gg_log_channel_helper_h_
#define _gg_log_channel_helper_h_

#include "gg/log/channel/channel_defs.h"
#include "gg/log/logger_defs.h"

namespace gg::log
{
    template <typename CHANNEL>
    class channel_helper final
    {
    public:

        // type definitions

        typedef CHANNEL channel;

        // constructors

        channel_helper(level level, channel_flags flags, bool8 enabled) noexcept
        {
            channel::create();
            channel::get_instance().set_flags(flags);
            channel::get_instance().set_level(level);
            channel::get_instance().is_enabled(enabled);
        }

        ~channel_helper(void) noexcept
        {
            channel::destroy();
        }
    };
}

#endif // _gg_log_channel_helper_h_
