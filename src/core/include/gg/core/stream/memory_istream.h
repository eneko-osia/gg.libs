#ifndef _gg_memory_istream_h_
#define _gg_memory_istream_h_

// include files

#include "gg/core/stream/istream.h"

namespace gg
{
    class memory_buffer_ref;

    class memory_istream final : public istream<memory_istream>
    {
    public:

        // constructors

        memory_istream(
            memory_buffer_ref const & buffer,
            endian_mode endian_mode = endian::system_mode) noexcept;
        ~memory_istream(void) noexcept = default;

        // methods

        bool8 move(size_type position) noexcept;
        size_type read(void * buffer, size_type bytes) noexcept;
        size_type read_line(char8 * buffer, size_type max_size) noexcept;

        // inquiries

        bool8 is_valid(void) const noexcept
        {
            return true;
        }

    private:

        // attributes

        memory_buffer_ref const & m_buffer;
        size_type m_position;
    };
}

#endif // _gg_memory_istream_h_
