#ifndef _gg_gfx_opengl_context_base_h_
#define _gg_gfx_opengl_context_base_h_

#include "gg/gfx/context.h"
#include "gg/gfx/opengl/context/opengl_context_defs.h"

namespace gg::gfx
{
    class opengl_context_base : public context
    {
    public:

        // methods

        void
        clear(
            uint8 red,
            uint8 green,
            uint8 blue,
            uint8 alpha,
            opengl_clear_mode mode =
                opengl_clear_mode::color |
                opengl_clear_mode::depth |
                opengl_clear_mode::stencil) const noexcept;

    protected:

        // constructors

        opengl_context_base(void) noexcept = default;
        virtual ~opengl_context_base(void) noexcept = default;
    };
}

#endif // _gg_gfx_opengl_context_base_h_
