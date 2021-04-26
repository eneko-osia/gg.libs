#ifndef _gg_gfx_opengl_viewport_h_
#define _gg_gfx_opengl_viewport_h_

#include "gg/core/type/type.h"

namespace gg::gfx::opengl
{
    class viewport final
    {
    public:

        // constructors

        viewport(void) noexcept = default;
        ~viewport(void) noexcept = default;

        // methods

        bool8 disable(void) noexcept;
        bool8 enable(uint16 width, uint16 height) noexcept;
    };
}

#endif // _gg_gfx_opengl_viewport_h_
