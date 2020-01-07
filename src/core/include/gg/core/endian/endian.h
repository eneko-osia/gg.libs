#ifndef _gg_endian_h_
#define _gg_endian_h_

// include files

#include "gg/core/endian/endian_defs.h"

// namespace

namespace gg
{
    // namespace in charge of define endian utilities

    namespace endian
    {
#if defined(GG_MAC)
    static constexpr endian_mode system_mode = endian_mode::little_endian;
#elif defined(GG_LINUX)
    static constexpr endian_mode system_mode = endian_mode::little_endian;
#elif defined(GG_WINDOWS)
    static constexpr endian_mode system_mode = endian_mode::little_endian;
#else
    #error "Can't specify endian mode for unsupported platform"
#endif
    }
}

#endif // _gg_endian_h_
