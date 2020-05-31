#ifndef _gg_gfx_opengl_context_context_h_
#define _gg_gfx_opengl_context_context_h_

// include files

#include "gg/gfx/opengl/opengl_context_platform.h"

// namespace

namespace gg::gfx
{
    // class in charge of define open gl context

    class opengl_context final : public opengl_context_platform
    {
    public:

        // constructors

        opengl_context(void) noexcept;
        ~opengl_context(void) noexcept = default;

        // icontext override methods

        void finalize(void) noexcept override;
        bool8 init(void) noexcept override;
    };
}

#endif // _gg_gfx_opengl_context_context_h_
