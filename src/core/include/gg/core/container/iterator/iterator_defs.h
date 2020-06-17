#ifndef _gg_iterator_defs_h_
#define _gg_iterator_defs_h_

#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/enum.h"

namespace gg
{
    enum class iterator_type : uint8
    {
        no_const,
        is_const,
        max
    };

    GG_ENUM(iterator_type);

#if defined(GG_DEBUG)
    static constexpr string_ref iterator_type_descriptors[] = {
        GG_TEXT("no_const"),
        GG_TEXT("is_const")
    };

    GG_ASSERT_STATIC(
        enums::cast(iterator_type::max) ==
            sizeof(iterator_type_descriptors) /
                sizeof(iterator_type_descriptors[0]),
        "descriptor missing for iterator_type_descriptors enumeration");
#endif
}

#endif // _gg_iterator_defs_h_
