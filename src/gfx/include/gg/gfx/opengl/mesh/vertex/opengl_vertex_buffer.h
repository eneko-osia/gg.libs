#ifndef _gg_gfx_opengl_vertex_buffer_h_
#define _gg_gfx_opengl_vertex_buffer_h_

#include "gg/core/type/type.h"

namespace gg::gfx
{
    class opengl_vertex_buffer
    {
    public:

        // constructors

        opengl_vertex_buffer(void) noexcept;
        ~opengl_vertex_buffer(void) noexcept;

        // methods

        void finalize(void) noexcept;
        bool8 init(
            void const * vertexes,
            uint32 bytes_per_vertex,
            uint32 num_vertex) noexcept;

        void reset(void) noexcept;
        void upload(void) noexcept;

        // accessors

        uint32 get_bytes_per_vertex(void) const noexcept
        {
            return m_bytes_per_vertex;
        }

        uint32 get_num_vertex(void) const noexcept
        {
            return m_num_vertex;
        }

    private:

        uint32 m_handle;
        uint32 m_bytes_per_vertex;
        uint32 m_num_vertex;
    };
}

#endif // _gg_gfx_opengl_vertex_buffer_h_
