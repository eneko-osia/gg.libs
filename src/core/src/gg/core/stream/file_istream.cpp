#include "gg/core/stream/file_istream.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg
{
//==============================================================================

file_istream::file_istream(
    string_ref const & filename,
    stream_mode stream_mode,
    endian_mode endian_mode) noexcept
    : m_file(nullptr)
    , m_position(0)
    , m_size(0)
    , m_endian_mode(endian_mode)
{
    m_file =
        fopen(filename.begin(), stream_mode::binary == stream_mode ? "rb" : "r");

    if (is_valid())
    {
        fseek(m_file, 0, SEEK_END);
        m_size = type::cast_static<uint32>(ftell(m_file));
        rewind(m_file);
    }
}

file_istream::file_istream(FILE * file, endian_mode endian_mode) noexcept
    : m_file(file)
    , m_position(0)
    , m_size(0)
    , m_endian_mode(endian_mode)
{
    if (is_valid())
    {
        fseek(m_file, 0, SEEK_END);
        m_size = type::cast_static<uint32>(ftell(m_file));
        rewind(m_file);
    }
}

file_istream::~file_istream(void)
{
    close();
}

//==============================================================================

void file_istream::close(void) noexcept
{
    if (is_valid())
    {
        fclose(m_file);
        m_file = nullptr;
    }
}

bool8 file_istream::move(uint32 position) noexcept
{
    if ((position <= m_size) &&
        (0 == fseek(m_file, type::cast_static<long>(position), SEEK_SET)))
    {
        m_position = position;
        return true;
    }

    return false;
}

uint32 file_istream::read(void * buffer, uint32 size) noexcept
{
    if (buffer && (size > 0) && is_valid())
    {
        uint32 read_size =
            type::cast_static<uint32>(
                fread(
                    buffer,
                    1,
                    ((m_position + size) > m_size) ? m_size - m_position : size,
                     m_file));

        m_position += read_size;
        return read_size;
    }

    return 0;
}

uint32 file_istream::read(float32 & value) noexcept
{
    uint32 read_size = read(&value, sizeof(float32));

    if (read_size > 0 && !is_endian_mode(endian::system_mode))
    {
        union
        {
            float32 as_float;
            uint32  as_unsigned;
        } temp;

        temp.as_float = value;
        temp.as_unsigned = byte_swap::swap(temp.as_unsigned);
        value = temp.as_float;
    }

    return read_size;
}

uint32 file_istream::read(float64 & value) noexcept
{
    uint32 read_size = read(&value, sizeof(float64));

    if (read_size > 0 && !is_endian_mode(endian::system_mode))
    {
        union
        {
            float64 as_float;
            uint64  as_unsigned;
        } temp;

        temp.as_float = value;
        temp.as_unsigned = byte_swap::swap(temp.as_unsigned);
        value = temp.as_float;
    }

    return read_size;
}

//==============================================================================
}
//==============================================================================
