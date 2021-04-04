#ifndef _gg_gfx_opengl_context_linux_h_
#define _gg_gfx_opengl_context_linux_h_

#include "gg/core/pattern/handle.h"
#include "gg/gfx/opengl/context/opengl_context_base.h"

namespace gg::gfx
{
    class opengl_context_linux : public opengl_context_base
    {
    public:

        // methods

        bool8 disable(void) noexcept;
        bool8 enable(void) noexcept;
        void swap_buffer(void) noexcept;

    protected:

        // constructors

        opengl_context_linux(void) noexcept;
        ~opengl_context_linux(void) noexcept;

    private:

        // friendships

        friend class opengl_context_base;

        // methods

        void on_finalize(void) noexcept;
        bool8 on_init(opengl_context_info const & info) noexcept;

        // attributes

        handle m_context;
        handle m_display;
        uint32 m_window;
    };

    typedef opengl_context_linux opengl_context_platform;
}

#endif // _gg_gfx_opengl_context_linux_h_
