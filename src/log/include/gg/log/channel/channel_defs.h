#ifndef _gg_log_channel_defs_h_
#define _gg_log_channel_defs_h_

#include "gg/core/type/enum.h"

namespace gg::log
{
    enum class channel_flags : uint8
    {
        channel =   1 << 0,
        level =     1 << 1,
        time =      1 << 2,
        full =      channel | level | time
    };

    GG_ENUM(channel_flags);
}

#endif // _gg_log_channel_defs_h_
