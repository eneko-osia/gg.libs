#ifndef _gg_gfx_opengl_mesh_h_
#define _gg_gfx_opengl_mesh_h_

#include "gg/core/container/array/array_dynamic.h"
#include "gg/gfx/opengl/mesh/index/opengl_index_buffer.h"
#include "gg/gfx/opengl/mesh/vertex/opengl_vertex_buffer.h"

namespace gg::gfx
{
    class opengl_mesh
    {
    public:

        // constructors

        opengl_mesh(void) noexcept;
        ~opengl_mesh(void) noexcept;

        // static methods

        // static uint32 get_gl_mesh_type(mesh_type type);

        // methods

        void finalize(void) noexcept;
        bool8 init(
            void const * vertexes,
            uint32 bytes_per_vertex,
            uint32 num_vertex,
            void const * indexes,
            uint32 bytes_per_index,
            uint32 num_index) noexcept;

        void reset(void) noexcept;
        void upload(void) noexcept;

    private:

        // struct

        struct sub_mesh
        {
            uint32 m_num_index;
            uint32 m_start_index;
        };

        // type definitions

        typedef array_dynamic<sub_mesh> sub_mesh_array;

        // attributes

        uint32 m_handle;
        sub_mesh_array m_sub_meshes;
        opengl_index_buffer m_index_buffer;
        opengl_vertex_buffer m_vertex_buffer;
    };
}

#endif // _gg_gfx_opengl_mesh_h_
