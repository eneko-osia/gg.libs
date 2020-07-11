#include "gg/core/stream/memory_istream.h"

//==============================================================================

#include "gg/core/memory/memory_buffer_ref.h"
#include "gg/core/memory/memory.h"

//==============================================================================
namespace gg
{
//==============================================================================

memory_istream::memory_istream(
    memory_buffer_ref const & buffer,
    endian_mode endian_mode) noexcept
    : istream(endian_mode)
    , m_buffer(buffer)
    , m_position(0)
{
}

//==============================================================================

bool8 memory_istream::move(size_type position) noexcept
{
    GG_ASSERT(position <= m_buffer.size());
    m_position = position;
    return true;
}

size_type memory_istream::read(void * buffer, size_type size) noexcept
{
    GG_RETURN_VALUE_IF(m_position >= m_buffer.size(), 0);
    size_type read_size =
        ((m_position + size) > m_buffer.size()) ?
            m_buffer.size() - m_position : size;
    memory::copy(buffer, &m_buffer.get(m_position), read_size);
    m_position += read_size;
    return read_size;
}

size_type memory_istream::read_line(char8 * buffer, size_type max_size) noexcept
{
    size_type read_size = 0;
    for (size_type i = m_position; i < m_buffer.size(); ++i)
    {
        if ('\n' == m_buffer.get<char8>(i))
        {
            read_size = (i - m_position + 1);
            break;
        }
    }
    read_size = read_size ? read_size : (m_buffer.size() - m_position);
    return read(buffer, (read_size > max_size) ? max_size : read_size);
}

//==============================================================================
}
//==============================================================================
