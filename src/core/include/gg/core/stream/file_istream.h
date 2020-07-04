#ifndef _gg_file_istream_h_
#define _gg_file_istream_h_

#include "gg/core/stream/istream.h"
#include "gg/core/stream/stream_defs.h"
#include <cstdio>

namespace gg
{
    class string_ref;

    class file_istream final : public istream<file_istream>
    {
    public:

        // constructors

        file_istream(
            string_ref const & filename,
            stream_mode stream_mode,
            endian_mode endian_mode = endian::system_mode) noexcept;
        ~file_istream(void) noexcept;

        // methods

        void close(void) noexcept;
        bool8 move(uint32 position) noexcept;
        uint32 read(void * buffer, uint32 bytes) noexcept;

        template <typename STRING_TYPE>
        uint32 read_line(STRING_TYPE & line) noexcept
        {
            int line_max_size = type::cast_static<int>(line.max_size());
            if (fgets(line.c_str(), line_max_size, m_file))
            {
                uint32 line_size = type::cast_static<uint32>(line.size());
                m_position += line_size;
                return line_size;
            }
            return 0;
        }

        // accessors

        uint32 get_position(void) const noexcept
        {
            return m_position;
        }

        uint32 size(void) const noexcept
        {
            return m_size;
        }

        // inquiries

        bool8 is_valid(void) const noexcept
        {
            return nullptr != m_file;
        }

    private:

        // attributes

        FILE * m_file;
        uint32 m_position;
        uint32 m_size;
    };
}

#endif // _gg_file_istream_h_
