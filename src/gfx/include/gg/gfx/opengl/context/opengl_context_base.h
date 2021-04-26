#ifndef _gg_gfx_opengl_context_base_h_
#define _gg_gfx_opengl_context_base_h_

#include "gg/gfx/opengl/context/opengl_context_defs.h"

namespace gg::gfx::opengl
{
    struct context_info;

    class context_base
    {
    public:

        // methods

        void
        clear(
            uint8 red,
            uint8 green,
            uint8 blue,
            uint8 alpha,
            clear_mode mode =
                clear_mode::color |
                clear_mode::depth |
                clear_mode::stencil) const noexcept;

        void finalize(void) noexcept;
        bool8 init(context_info const & info) noexcept;

    protected:

        // constructors

        context_base(void) noexcept = default;
        ~context_base(void) noexcept = default;
    };
}

#endif // _gg_gfx_opengl_context_base_h_
