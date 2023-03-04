//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/shader/opengl_shader.h"

//==============================================================================

#include "gg/core/string/type/string_static.h"
#include "gg/gfx/opengl/debug/opengl_assert.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_shader::opengl_shader(shader_type type) noexcept
    : typeable<shader_type>(type)
    , m_shader_hw(0)
{
}

opengl_shader::~opengl_shader(void) noexcept
{
    GG_ASSERT(0 == m_shader_hw);
}

//==============================================================================

uint32
opengl_shader::compile(
    shader_type type,
    void const * shader[],
    uint32 size[],
    uint32 count) noexcept
{
    uint32 shader_hw = glCreateShader(get_gl_shader_type(type));

    if (0 != shader_hw)
    {
        glShaderSource(shader_hw, count, (GLchar const **) shader, (GLint *) size);
        glCompileShader(shader_hw);

        GLint status = 0;
        glGetShaderiv(shader_hw, GL_COMPILE_STATUS, &status);
        GG_RETURN_VALUE_IF(GL_FALSE == status, 0);
    }

    return shader_hw;
}

void opengl_shader::finalize(void) noexcept
{
    if (0 != m_shader_hw)
    {
        glDeleteShader(m_shader_hw);
        m_shader_hw = 0;
    }
}

uint32 opengl_shader::get_gl_shader_type(shader_type type) noexcept
{
    switch (type)
    {
        case shader_type::pixel_shader_type:
        {
            return GL_FRAGMENT_SHADER;
        }

        case shader_type::vertex_shader_type:
        {
            return GL_VERTEX_SHADER;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

bool8 opengl_shader::init(void const * shader[], uint32 size[], uint32 count) noexcept
{
    GG_RETURN_FALSE_IF((0 != m_shader_hw) || !shader || (0 == size));

    int32 has_compiler = 0;
    glGetIntegerv(GL_SHADER_COMPILER, &has_compiler);
    GG_ASSERT_GL_ERROR();

    if (0 == has_compiler)
    {
        return false;
    }

    // char8 define[] = "#define ENEKOS \n";
    // GLchar const * sources[2] = {define, (GLchar const *) shader};
    // GLint sizes[2] = {(GLint) strlen(define), (GLint) size};

    m_shader_hw = compile(get_type(), shader, size, count);
    return 0 != m_shader_hw;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
