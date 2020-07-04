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
    : istream(endian_mode)
    , m_file(nullptr)
    , m_position(0)
    , m_size(0)
{
    m_file =
        fopen(
            filename.c_str(),
            stream_mode::binary == stream_mode ? "rb" : "r");

    if (is_valid())
    {
        fseek(m_file, 0, SEEK_END);
        m_size = (uint32) ftell(m_file);
        rewind(m_file);
    }
}

file_istream::~file_istream(void)
{
    if (is_valid())
    {
        close();
    }
}

//==============================================================================

void file_istream::close(void) noexcept
{
    fclose(m_file);
    m_file = nullptr;
}

bool8 file_istream::move(uint32 position) noexcept
{
    GG_ASSERT(position <= m_size);
    if (0 == fseek(m_file, (long) position, SEEK_SET))
    {
        m_position = position;
        return true;
    }

    return false;
}

uint32 file_istream::read(void * buffer, uint32 size) noexcept
{
    size_t element_size =
        ((m_position + size) > m_size) ? m_size - m_position : size;
    uint32 read_size = (uint32) fread(buffer, element_size, 1, m_file);
    m_position += read_size;
    return read_size;
}

//==============================================================================
}
//==============================================================================
