#ifndef _gg_memory_defs_h_
#define _gg_memory_defs_h_

// include files

#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/enum.h"

// namespace

namespace gg
{
    // enumeration

    enum class memory_owner_mode : uint8
    {
        is_not_owner,
        is_owner,
        max
    };

    GG_ENUM(memory_owner_mode);

#if defined(GG_DEBUG)
    // enumeration descriptors

    static constexpr string_ref memory_owner_mode_descriptors[] = {
        GG_TEXT("is_not_owner"),
        GG_TEXT("is_owner")
    };

    // static assert

    GG_STATIC_ASSERT(
        enums::cast(memory_owner_mode::max) ==
            sizeof(memory_owner_mode_descriptors) /
                sizeof(memory_owner_mode_descriptors[0]),
        "descriptor missing for memory_owner_mode enumeration");
#endif
}

#endif // _gg_memory_defs_h_
