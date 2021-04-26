#ifndef _gg_gfx_opengl_context_h_
#define _gg_gfx_opengl_context_h_

#include "gg/gfx/opengl/context/opengl_context_platform.h"

namespace gg::gfx::opengl
{
    class context final : public context_platform
    {
    public:

        // constructors

        context(void) noexcept = default;
        ~context(void) noexcept = default;
    };
}

#endif // _gg_gfx_opengl_context_h_
