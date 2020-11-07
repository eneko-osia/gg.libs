#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/rasterizer/opengl_rasterizer.h"

//==============================================================================

#include "gg/core/debug/assert.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_rasterizer::opengl_rasterizer(void) noexcept
    : m_alpha_blend(enable_mode::disable)
    , m_alpha_blend_mode(blend_mode::add)
    , m_alpha_blend_dst_mode(blend_function_mode::one)
    , m_alpha_blend_src_mode(blend_function_mode::one)
    , m_alpha_test(enable_mode::disable)
    , m_alpha_test_mode(function_mode::always)
    , m_alpha_test_value(0.0f)
    , m_culling(enable_mode::disable)
    , m_culling_mode(culling_mode::back_face)
    , m_depth(enable_mode::disable)
    , m_depth_mode(function_mode::always)
    , m_front_face_mode(front_face_mode::clockwise)
    , m_polygon_face_mode(polygon_face_mode::back_and_front_face)
    , m_polygon_fill_mode(polygon_fill_mode::fill)
{
}

//==============================================================================

void opengl_rasterizer::activate(void) const noexcept
{
    if (enable_mode::enable == get_alpha_blend())
    {
        enable_alpha_blend(
            get_alpha_blend_mode(),
            get_alpha_blend_src_mode(),
            get_alpha_blend_dst_mode());
    }
    else
    {
        disable_alpha_blend();
    }

    if (enable_mode::enable == get_alpha_test())
    {
        enable_alpha_test(get_alpha_test_mode(), get_alpha_test_value());
    }
    else
    {
        disable_alpha_test();
    }

    if (enable_mode::enable == get_culling())
    {
        enable_culling(get_culling_mode());
    }
    else
    {
        disable_culling();
    }

    if (enable_mode::enable == get_depth())
    {
        enable_depth(get_depth_mode());
    }
    else
    {
        disable_depth();
    }

    define_polygon(get_polygon_face_mode(), get_polygon_fill_mode());
    define_front_face(get_front_face_mode());
}

void opengl_rasterizer::define_front_face(front_face_mode mode) noexcept
{
    glFrontFace(get_gl_front_face_mode(mode));
    // ASSERT_GL_ERROR();
}

void
opengl_rasterizer::define_polygon(
    polygon_face_mode face,
    polygon_fill_mode fill) noexcept
{
#if !defined(GG_ANDROID)
    glPolygonMode(
        get_gl_polygon_face_mode(face),
        get_gl_polygon_fill_mode(fill));
    // ASSERT_GL_ERROR();
#endif
}

void
opengl_rasterizer::enable_alpha_blend(
    blend_mode mode,
    blend_function_mode source,
    blend_function_mode destination) noexcept
{
    glEnable(GL_BLEND);
    // ASSERT_GL_ERROR();
    glBlendEquation(get_gl_blend_mode(mode));
    // ASSERT_GL_ERROR();
    glBlendFunc(get_gl_blend_function_mode(source),
                get_gl_blend_function_mode(destination));
    // ASSERT_GL_ERROR();
}

void opengl_rasterizer::enable_alpha_test(function_mode mode, float32 value) noexcept
{
#if !defined(GG_ANDROID)
    glEnable(GL_ALPHA_TEST);
    // ASSERT_GL_ERROR();
    glAlphaFunc(get_gl_function_mode(mode), value);
    // ASSERT_GL_ERROR();
#endif
}

void opengl_rasterizer::enable_culling(culling_mode mode) noexcept
{
    glEnable(GL_CULL_FACE);
    // ASSERT_GL_ERROR();
    glCullFace(get_gl_culling_mode(mode));
    // ASSERT_GL_ERROR();
}

void opengl_rasterizer::enable_depth(function_mode mode) noexcept
{
    glEnable(GL_DEPTH_TEST);
    // ASSERT_GL_ERROR();
    glDepthMask(GL_TRUE);
    // ASSERT_GL_ERROR();
    glDepthFunc(get_gl_function_mode(mode));
    // ASSERT_GL_ERROR();
}

void opengl_rasterizer::disable_alpha_blend(void) noexcept
{
    glDisable(GL_BLEND);
    // ASSERT_GL_ERROR();
}

void opengl_rasterizer::disable_alpha_test(void) noexcept
{
#if !defined(GG_ANDROID)
    glDisable(GL_ALPHA_TEST);
    // ASSERT_GL_ERROR();
#endif
}

void opengl_rasterizer::disable_culling(void) noexcept
{
    glDisable(GL_CULL_FACE);
    // ASSERT_GL_ERROR();
}

void opengl_rasterizer::disable_depth(void) noexcept
{
    glDisable(GL_DEPTH_TEST);
    // ASSERT_GL_ERROR();
    glDepthMask(GL_FALSE);
    // ASSERT_GL_ERROR();
}

uint32 opengl_rasterizer::get_gl_blend_function_mode(blend_function_mode mode) noexcept
{
    switch (mode)
    {
        case blend_function_mode::constant_alpha:
        {
            return GL_CONSTANT_ALPHA;
        }

        case blend_function_mode::constant_color:
        {
            return GL_CONSTANT_COLOR;
        }

        case blend_function_mode::dst_alpha:
        {
            return GL_DST_ALPHA;
        }

        case blend_function_mode::dst_color:
        {
            return GL_DST_COLOR;
        }

        case blend_function_mode::one:
        {
            return GL_ONE;
        }

        case blend_function_mode::one_minus_constant_alpha:
        {
            return GL_ONE_MINUS_CONSTANT_ALPHA;
        }

        case blend_function_mode::one_minus_constant_color:
        {
            return GL_ONE_MINUS_CONSTANT_COLOR;
        }

        case blend_function_mode::one_minus_dst_alpha:
        {
            return GL_ONE_MINUS_DST_ALPHA;
        }

        case blend_function_mode::one_minus_dst_color:
        {
            return GL_ONE_MINUS_DST_COLOR;
        }

        case blend_function_mode::one_minus_src_color:
        {
            return GL_ONE_MINUS_SRC_COLOR;
        }

        case blend_function_mode::src_alpha:
        {
            return GL_SRC_ALPHA;
        }

        case blend_function_mode::one_minus_src_alpha:
        {
            return GL_ONE_MINUS_SRC_ALPHA;
        }

        case blend_function_mode::src_alpha_saturate:
        {
            return GL_SRC_ALPHA_SATURATE;
        }

        case blend_function_mode::src_color:
        {
            return GL_SRC_COLOR;
        }

        case blend_function_mode::zero:
        {
            return GL_ZERO;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_blend_mode(blend_mode mode) noexcept
{
    switch (mode)
    {
        case blend_mode::add:
        {
            return GL_FUNC_ADD;
        }

        case blend_mode::reverse_subtract:
        {
            return GL_FUNC_REVERSE_SUBTRACT;
        }

        case blend_mode::subtract:
        {
            return GL_FUNC_SUBTRACT;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_culling_mode(culling_mode mode) noexcept
{
    switch (mode)
    {
        case culling_mode::back_face:
        {
            return GL_BACK;
        }

        case culling_mode::front_face:
        {
            return GL_FRONT;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_enable_mode(enable_mode mode) noexcept
{
    switch (mode)
    {
        case enable_mode::disable:
        {
            return GL_FALSE;
        }

        case enable_mode::enable:
        {
            return GL_TRUE;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_front_face_mode(front_face_mode mode) noexcept
{
    switch (mode)
    {
        case front_face_mode::clockwise:
        {
            return GL_CW;
        }

        case front_face_mode::counter_clockwise:
        {
            return GL_CCW;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_function_mode(function_mode mode) noexcept
{
    switch (mode)
    {
        case function_mode::always:
        {
            return GL_ALWAYS;
        }

        case function_mode::equal:
        {
            return GL_EQUAL;
        }

        case function_mode::greater:
        {
            return GL_GREATER;
        }

        case function_mode::greaterequal:
        {
            return GL_GEQUAL;
        }

        case function_mode::less:
        {
            return GL_LESS;
        }

        case function_mode::lessequal:
        {
            return GL_LEQUAL;
        }

        case function_mode::never:
        {
            return GL_NEVER;
        }

        case function_mode::notequal:
        {
            return GL_NOTEQUAL;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_polygon_face_mode(polygon_face_mode mode) noexcept
{
    switch (mode)
    {
        case polygon_face_mode::back_and_front_face:
        {
            return GL_FRONT_AND_BACK;
        }

        case polygon_face_mode::back_face:
        {
            return GL_BACK;
        }

        case polygon_face_mode::front_face:
        {
            return GL_FRONT;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }
}

uint32 opengl_rasterizer::get_gl_polygon_fill_mode(polygon_fill_mode mode) noexcept
{
#if !defined(GG_ANDROID)

    switch (mode)
    {
        case polygon_fill_mode::fill:
        {
            return GL_FILL;
        }

        case polygon_fill_mode::line:
        {
            return GL_LINE;
        }

        case polygon_fill_mode::point:
        {
            return GL_POINT;
        }

        default:
        {
            GG_ASSERT_FAILED();
            return 0;
        }
    }

#else

    return 0;

#endif
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
