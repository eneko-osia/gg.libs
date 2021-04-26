#ifndef _gg_gfx_opengl_context_defs_h_
#define _gg_gfx_opengl_context_defs_h_

#include "gg/core/type/enum.h"

namespace gg::gfx::opengl
{
    enum class clear_mode : uint8
    {
        color =     1 << 0,
        depth =     1 << 1,
        stencil =   1 << 2
    };

    GG_ENUM(clear_mode);
}

#endif // _gg_gfx_opengl_context_defs_h_
