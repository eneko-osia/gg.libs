#ifndef _gg_gfx_opengl_effect_h_
#define _gg_gfx_opengl_effect_h_

#include "gg/gfx/opengl/rasterizer/rasterizer.h"

namespace gg::gfx
{
    class opengl_effect
    {
    public:

        // constructors

        opengl_effect(void) noexcept
            : m_rasterizer()
            , m_enabled(true)
        {
        }

        ~opengl_effect(void) noexcept = default;

        // methods

        void upload(void) const noexcept
        {
            m_rasterizer.activate();
        }

        // inquiries

        bool8 is_enabled(void) const noexcept
        {
            return m_enabled;
        }

        void is_enabled(bool8 enabled) noexcept
        {
            m_enabled = enabled;
        }

    private:

        // attributes

        opengl_rasterizer m_rasterizer;
        bool8 m_enabled;
    };
}

#endif // _gg_gfx_opengl_effect_h_
