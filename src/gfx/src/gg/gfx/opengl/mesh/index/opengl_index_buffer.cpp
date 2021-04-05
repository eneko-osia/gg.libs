//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/mesh/index/opengl_index_buffer.h"

//==============================================================================

#include "gg/core/macro/macro.h"
#include "gg/gfx/opengl/debug/opengl_assert.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_index_buffer::opengl_index_buffer(void) noexcept
    : m_handle(0)
    , m_bytes_per_index(0)
    , m_num_index(0)

{
}

//==============================================================================

void opengl_index_buffer::finalize(void) noexcept
{
    GG_RETURN_IF(0 == m_handle);
    glDeleteBuffers(1, &m_handle);
    m_handle = 0;
}

bool8
opengl_index_buffer::init(
    void const * indexes,
    uint32 bytes_per_index,
    uint32 num_index) noexcept
{
    GG_RETURN_FALSE_IF(0 != m_handle);
    GG_RETURN_FALSE_IF(!indexes);
    GG_RETURN_FALSE_IF(0 == bytes_per_index);
    GG_RETURN_FALSE_IF(0 == num_index);

    glGenBuffers(1, &m_handle);
    GG_ASSERT_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    GG_ASSERT_GL_ERROR();

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        bytes_per_index * num_index,
        indexes,
        GL_STATIC_DRAW);
    GG_ASSERT_GL_ERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GG_ASSERT_GL_ERROR();

    m_bytes_per_index = bytes_per_index;
    m_num_index = num_index;
    return true;
}

void opengl_index_buffer::reset(void) noexcept
{
    GG_ASSERT(0 != m_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GG_ASSERT_GL_ERROR();
}

void opengl_index_buffer::upload(void) noexcept
{
    GG_ASSERT(0 != m_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    GG_ASSERT_GL_ERROR();
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
