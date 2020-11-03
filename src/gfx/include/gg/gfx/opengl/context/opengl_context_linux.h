#ifndef _gg_gfx_opengl_context_linux_h_
#define _gg_gfx_opengl_context_linux_h_

#include "gg/gfx/opengl/context/opengl_context_base.h"

typedef struct __GLXcontextRec * GLXContext;

namespace gg::gfx
{
    // forward declarations

    struct opengl_context_info;

    // type definitions

    typedef class opengl_context_linux opengl_context_platform;

    // class in charge of define a linux opengl context

    class opengl_context_linux : public opengl_context_base
    {
    protected:

        // constructors

        opengl_context_linux(void) noexcept;
        virtual ~opengl_context_linux(void) noexcept = default;

    private:

        // context override methods

        void on_finalize(void) noexcept override final;
        bool8 on_init(context_info const * info) noexcept override final;

        // methods

        bool8 on_init(opengl_context_info const * info) noexcept;

    private:

        // attributes

        GLXContext m_context;
        uint32 m_window;
    };
}

#endif // _gg_gfx_opengl_context_linux_h_

