#ifndef _gg_file_istream_h_
#define _gg_file_istream_h_

// include files

#include "gg/core/endian/endian.h"
#include "gg/core/stream/stream_defs.h"
#include "gg/core/utils/byte_swap.h"
#include <cstdio>

// namespace

namespace gg
{
    // forward declarations

    class string_ref;

    // class in charge of define a file input stream

    class file_istream final
    {
    public:

        // constructors

        file_istream(
            string_ref const & filename,
            stream_mode stream_mode,
            endian_mode endian_mode = endian::system_mode) noexcept;

        file_istream(
            FILE * file,
            endian_mode endian_mode = endian::system_mode) noexcept;

        ~file_istream(void) noexcept;

        // methods

        void close(void) noexcept;
        bool8 move(uint32 position) noexcept;

        uint32 read(bool8 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(int8 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(uint8 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(int16 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(uint16 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(int32 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(uint32 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(int64 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(uint64 & value) noexcept
        {
            return read_internal(value);
        }

        uint32 read(float32 & value) noexcept;
        uint32 read(float64 & value) noexcept;
        uint32 read(void * buffer, uint32 bytes) noexcept;

        template <typename STRING_TYPE>
        uint32 read_line(STRING_TYPE & line) noexcept
        {
            if (is_valid())
            {
                if (fgets(
                    line.begin(),
                    type::cast_static<int>(line.max_size()),
                    m_file))
                {
                    m_position += type::cast_static<uint32>(line.size());
                    return type::cast_static<uint32>(line.size());
                }
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

        bool8 is_endian_mode(endian_mode mode) const noexcept
        {
            return m_endian_mode == mode;
        }

        bool8 is_valid(void) const noexcept
        {
            return nullptr != m_file;
        }

    private:

        // methods

        template <typename TYPE>
        uint32 read_internal(TYPE & value) noexcept
        {
            uint32 read_size = read(&value, sizeof(TYPE));

            if ((read_size > 0) && !is_endian_mode(endian::system_mode))
            {
                value = byte_swap::swap(value);
            }

            return read_size;
        }

    private:

        // attributes

        FILE * m_file;
        uint32 m_position;
        uint32 m_size;
        endian_mode m_endian_mode;
    };
}

#endif // _gg_file_istream_h_
