#ifndef _gg_stream_defs_h_
#define _gg_stream_defs_h_

// include files

#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/enum.h"

// namespace

namespace gg
{
    // enumeration

    enum class stream_mode : uint8
    {
        binary,
        text,
        max
    };

    GG_ENUM(stream_mode);

#if defined(GG_DEBUG)
    // enumeration descriptors

    static constexpr string_ref stream_mode_descriptors[] = {
        GG_TEXT("binary"),
        GG_TEXT("text")
    };

    // static assert

    GG_STATIC_ASSERT(
        enums::cast(stream_mode::max) ==
            sizeof(stream_mode_descriptors) /
                sizeof(stream_mode_descriptors[0]),
        "descriptor missing for stream_mode enumeration");
#endif
}

#endif // _gg_stream_defs_h_
