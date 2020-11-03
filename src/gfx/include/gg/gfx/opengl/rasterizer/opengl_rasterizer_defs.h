#ifndef _gg_gfx_opengl_rasterizer_defs_h_
#define _gg_gfx_opengl_rasterizer_defs_h_

#include "gg/core/type/enum.h"

namespace gg::gfx
{
    enum class blend_function_mode : uint8
    {
        constant_alpha,
        constant_color,
        dst_alpha,
        dst_color,
        one,
        one_minus_constant_alpha,
        one_minus_constant_color,
        one_minus_dst_alpha,
        one_minus_dst_color,
        one_minus_src_color,
        src_alpha,
        one_minus_src_alpha,
        src_alpha_saturate,
        src_color,
        zero
    };

    GG_ENUM(blend_function_mode);

    enum class blend_mode : uint8
    {
        add,
        reverse_subtract,
        subtract
    };

    GG_ENUM(blend_mode);

    enum class culling_mode : uint8
    {
        back_face,
        front_face
    };

    GG_ENUM(culling_mode);

    enum class enable_mode : uint8
    {
        disable,
        enable
    };

    GG_ENUM(enable_mode);

    enum class front_face_mode : uint8
    {
        clockwise,
        counter_clockwise
    };

    GG_ENUM(front_face_mode);

    enum class function_mode : uint8
    {
        always,
        equal,
        greater,
        greaterequal,
        less,
        lessequal,
        never,
        notequal
    };

    GG_ENUM(function_mode);

    enum class polygon_face_mode : uint8
    {
        back_and_front_face,
        back_face,
        front_face
    };

    GG_ENUM(polygon_face_mode);

    enum class polygon_fill_mode : uint8
    {
        fill,
        line,
        point
    };

    GG_ENUM(polygon_fill_mode);
}

#endif // _gg_gfx_opengl_rasterizer_defs_h_
