#ifndef _gg_gfx_shader_defs_h_
#define _gg_gfx_shader_defs_h_

#include "gg/core/type/enum.h"

#if defined(GG_DEBUG)
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#endif

namespace gg::gfx
{
    enum class shader_type : uint8
    {
        pixel_shader_type,
        vertex_shader_type,
        max
    };

    GG_ENUM(shader_type);

#if defined(GG_DEBUG)
    static constexpr char8 const * k_shader_type_descriptors[] = {
        GG_TEXT("pixel_shader_type"),
        GG_TEXT("vertex_shader_type")
    };

    GG_ASSERT_STATIC(
        enums::cast(shader_type::max) ==
            sizeof(k_shader_type_descriptors) /
                sizeof(k_shader_type_descriptors[0]),
        "descriptor missing for shader_type_descriptors enumeration");
#endif
}

#endif // _gg_gfx_shader_defs_h_
