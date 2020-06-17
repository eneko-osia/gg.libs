#ifndef _gg_endian_defs_h_
#define _gg_endian_defs_h_

#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/enum.h"

namespace gg
{
    enum class endian_mode : uint8
    {
        big_endian,
        little_endian,
        max
    };

    GG_ENUM(endian_mode);

#if defined(GG_DEBUG)
    static constexpr string_ref endian_mode_descriptors[] = {
        GG_TEXT("big_endian"),
        GG_TEXT("little_endian")
    };

    GG_ASSERT_STATIC(
        enums::cast(endian_mode::max) ==
            sizeof(endian_mode_descriptors) /
                sizeof(endian_mode_descriptors[0]),
        "descriptor missing for endian_mode_descriptors enumeration");
#endif
}

#endif // _gg_endian_defs_h_
