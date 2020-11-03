#include "gg/gfx/opengl/rasterizer/opengl_rasterizer.h"

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
}
//==============================================================================
