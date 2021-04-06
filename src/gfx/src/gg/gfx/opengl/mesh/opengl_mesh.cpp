//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/mesh/opengl_mesh.h"

//==============================================================================

#include "gg/core/macro/macro.h"
#include "gg/gfx/opengl/debug/opengl_assert.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_mesh::opengl_mesh(void) noexcept
    : m_handle(0)
    , m_index_buffer()
    , m_vertex_buffer()

{
}

opengl_mesh::~opengl_mesh(void) noexcept
{
    GG_ASSERT(0 == m_handle);
}

//==============================================================================

void opengl_mesh::finalize(void) noexcept
{
    GG_RETURN_IF(0 == m_handle);

    m_index_buffer.finalize();
    m_vertex_buffer.finalize();

    glDeleteVertexArrays(1, &m_handle);
    GG_ASSERT_GL_ERROR();
    m_handle = 0;
}

bool8
opengl_mesh::init(
    void const * vertexes,
    uint32 bytes_per_vertex,
    uint32 num_vertex,
    void const * indexes,
    uint32 bytes_per_index,
    uint32 num_index) noexcept
{
    GG_RETURN_FALSE_IF(0 != m_handle);

    glGenVertexArrays(1, &m_handle);
    GG_ASSERT_GL_ERROR();

    glBindVertexArray(m_handle);
    GG_ASSERT_GL_ERROR();

    bool8 result = m_vertex_buffer.init(vertexes, bytes_per_vertex, num_vertex);
    if (result)
    {
        result = m_index_buffer.init(indexes, bytes_per_index, num_index);
    }

    glBindVertexArray(0);
    GG_ASSERT_GL_ERROR();

    return result;
}

void opengl_mesh::reset(void) noexcept
{
    GG_ASSERT(0 != m_handle);

    m_index_buffer.reset();
    m_vertex_buffer.reset();

    glBindVertexArray(0);
    GG_ASSERT_GL_ERROR();
}

void opengl_mesh::upload(void) noexcept
{
    GG_ASSERT(0 != m_handle);
    glBindVertexArray(m_handle);
    GG_ASSERT_GL_ERROR();

    m_vertex_buffer.upload();
    m_index_buffer.upload();
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
