//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/mesh/vertex/opengl_vertex_buffer.h"

//==============================================================================

#include "gg/core/macro/macro.h"
#include "gg/gfx/opengl/debug/opengl_assert.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_vertex_buffer::opengl_vertex_buffer(void) noexcept
    : m_handle(0)
    , m_bytes_per_vertex(0)
    , m_num_vertex(0)

{
}

opengl_vertex_buffer::~opengl_vertex_buffer(void) noexcept
{
    GG_ASSERT(0 == m_handle);
}

//==============================================================================

void opengl_vertex_buffer::finalize(void) noexcept
{
    GG_RETURN_IF(0 == m_handle);
    glDeleteBuffers(1, &m_handle);
    m_handle = 0;
}

bool8
opengl_vertex_buffer::init(
    void const * vertexes,
    uint32 bytes_per_vertex,
    uint32 num_vertex) noexcept
{
    GG_RETURN_FALSE_IF(0 != m_handle);
    GG_RETURN_FALSE_IF(!vertexes);
    GG_RETURN_FALSE_IF(0 == bytes_per_vertex);
    GG_RETURN_FALSE_IF(0 == num_vertex);

    glGenBuffers(1, &m_handle);
    GG_ASSERT_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    GG_ASSERT_GL_ERROR();

    glBufferData(
        GL_ARRAY_BUFFER,
        bytes_per_vertex * num_vertex,
        vertexes,
        GL_STATIC_DRAW);
    GG_ASSERT_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GG_ASSERT_GL_ERROR();

    m_bytes_per_vertex = bytes_per_vertex;
    m_num_vertex = num_vertex;
    return true;
}

void opengl_vertex_buffer::reset(void) noexcept
{
    GG_ASSERT(0 != m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GG_ASSERT_GL_ERROR();
}

void opengl_vertex_buffer::upload(void) noexcept
{
    GG_ASSERT(0 != m_handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    GG_ASSERT_GL_ERROR();
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
