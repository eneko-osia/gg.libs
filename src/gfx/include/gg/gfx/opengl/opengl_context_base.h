#ifndef _gg_gfx_opengl_context_base_h_
#define _gg_gfx_opengl_context_base_h_

// include files

#include "gg/gfx/context.h"

// namespace

namespace gg::gfx
{
    // class in charge of define a base opengl context

    class opengl_context_base : public context
    {
    protected:

        // constructors

        opengl_context_base(void) noexcept = default;
        virtual ~opengl_context_base(void) noexcept = default;
    };
}

#endif // _gg_gfx_opengl_context_base_h_
