#ifndef _gg_log_logger_defs_h_
#define _gg_log_logger_defs_h_

#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/enum.h"
#include "gg/core/container/array/array_static.h"

namespace gg::log
{
    enum class flags : uint8
    {
        channel =   1 << 0,
        level =     1 << 1,
        time =      1 << 2,
        thread =    1 << 3,
        full =      channel | level | time | thread
    };

    GG_ENUM(flags);

    enum class level : uint8
    {
        error,
        warning,
        normal,
        debug,
        verbose,
        max
    };

    GG_ENUM(level);

    static constexpr char8 const * k_level_descriptors[] = {
        GG_TEXT("error"),
        GG_TEXT("warning"),
        GG_TEXT("normal"),
        GG_TEXT("debug"),
        GG_TEXT("verbose")
    };

    static const array_static<string_ref, type::cast_static<size_type>(1)> k_level = { string_ref(GG_TEXT("")) };

    GG_ASSERT_STATIC(
        enums::cast(level::max) ==
            sizeof(k_level_descriptors) / sizeof(k_level_descriptors[0]),
        "descriptor missing for level_descriptors enumeration");
}

#endif // _gg_log_logger_defs_h_
