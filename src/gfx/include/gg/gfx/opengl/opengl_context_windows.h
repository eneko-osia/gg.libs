#ifndef _gg_gfx_opengl_context_windows_h_
#define _gg_gfx_opengl_context_windows_h_

// include files

#include "gg/gfx/opengl/opengl_context_base.h"

// namespace

namespace gg::gfx
{
    // type definitions

    typedef class opengl_context_windows opengl_context_platform;

    // class in charge of define a windows opengl context

    class opengl_context_windows : public opengl_context_base
    {
    protected:

        // constructors

        opengl_context_windows(void) = default;
        virtual ~opengl_context_windows(void) = default;
    };
}

#endif // _gg_gfx_opengl_context_windows_h_

