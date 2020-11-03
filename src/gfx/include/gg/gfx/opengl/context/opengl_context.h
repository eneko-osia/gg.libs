#ifndef _gg_gfx_opengl_context_h_
#define _gg_gfx_opengl_context_h_

#include "gg/gfx/opengl/context/opengl_context_platform.h"

namespace gg::gfx
{
    class opengl_context final : public opengl_context_platform
    {
    public:

        // constructors

        opengl_context(void) noexcept = default;
        ~opengl_context(void) noexcept = default;
    };
}

#endif // _gg_gfx_opengl_context_h_
