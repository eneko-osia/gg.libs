#ifndef _gg_gfx_opengl_shader_h_
#define _gg_gfx_opengl_shader_h_

#include "gg/core/pattern/typeable.h"
#include "gg/gfx/shader/shader_defs.h"

namespace gg::gfx
{
    class opengl_shader : public typeable<shader_type>
    {
    public:

        // constructors

        opengl_shader(shader_type type) noexcept;
        ~opengl_shader(void) noexcept;

        // methods

        void finalize(void) noexcept;
        bool8 init(void const * shader[], uint32 size[], uint32 count) noexcept;

        // accessors

        uint32 get_shader_hw(void) const noexcept
        {
            return m_shader_hw;
        }

    private:

        // static methods

        static uint32
        compile(
            shader_type type,
            void const * shader[],
            uint32 size[],
            uint32 count) noexcept;
        static uint32 get_gl_shader_type(shader_type type) noexcept;

    private:

        // attributes

        uint32 m_shader_hw;
    };
}

#endif // _gg_gfx_opengl_shader_h_
