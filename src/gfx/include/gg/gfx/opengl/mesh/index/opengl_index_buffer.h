#ifndef _gg_gfx_opengl_index_buffer_h_
#define _gg_gfx_opengl_index_buffer_h_

#include "gg/core/type/type.h"

namespace gg::gfx
{
    class opengl_index_buffer
    {
    public:

        // constructors

        opengl_index_buffer(void) noexcept;
        ~opengl_index_buffer(void) noexcept = default;

        // methods

        void finalize(void) noexcept;
        bool8 init(
            void const * indexes,
            uint32 bytes_per_index,
            uint32 num_index) noexcept;

        void reset(void) noexcept;
        void upload(void) noexcept;

        // accessors

        uint32 get_bytes_per_index(void) const noexcept
        {
            return m_bytes_per_index;
        }

        uint32 get_num_index(void) const noexcept
        {
            return m_num_index;
        }

    private:

        uint32 m_handle;
        uint32 m_bytes_per_index;
        uint32 m_num_index;
    };
}

#endif // _gg_gfx_opengl_index_buffer_h_
