#ifndef _gg_gfx_opengl_context_windows_h_
#define _gg_gfx_opengl_context_windows_h_

// include files

#include "gg/gfx/opengl/opengl_context_base.h"
#include <windows.h>

// namespace

namespace gg::gfx
{
    // forward declarations

    struct opengl_context_info;

    // type definitions

    typedef class opengl_context_windows opengl_context_platform;

    // class in charge of define a windows opengl context

    class opengl_context_windows : public opengl_context_base
    {
    protected:

        // constructors

        opengl_context_windows(void) noexcept;
        virtual ~opengl_context_windows(void) noexcept = default;

    private:

        // context override methods

        void on_finalize(void) noexcept override final;
        bool8 on_init(context_info const * info) noexcept override final;

        // methods

        bool8 on_init(opengl_context_info const * info) noexcept;

    private:

        // attributes

        HDC m_context;
        HGLRC m_render_context;
    };
}

#endif // _gg_gfx_opengl_context_windows_h_

