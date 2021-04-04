#ifndef _gg_gfx_opengl_context_base_h_
#define _gg_gfx_opengl_context_base_h_

#include "gg/gfx/opengl/context/opengl_context_defs.h"

namespace gg::gfx
{
    struct opengl_context_info;

    class opengl_context_base
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

        void finalize(void) noexcept;
        bool8 init(opengl_context_info const & info) noexcept;

    protected:

        // constructors

        opengl_context_base(void) noexcept = default;
        ~opengl_context_base(void) noexcept = default;
    };
}

#endif // _gg_gfx_opengl_context_base_h_
