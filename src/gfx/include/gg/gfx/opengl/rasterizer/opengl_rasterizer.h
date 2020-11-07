#ifndef _gg_gfx_opengl_rasterizer_h_
#define _gg_gfx_opengl_rasterizer_h_

#include "gg/gfx/opengl/rasterizer/opengl_rasterizer_defs.h"

namespace gg::gfx
{
    class opengl_rasterizer
    {
    public:

        // constructors

        opengl_rasterizer(void) noexcept;
        ~opengl_rasterizer(void) noexcept = default;

        // static methods

        static void define_front_face(front_face_mode mode) noexcept;
        static void define_polygon(polygon_face_mode face, polygon_fill_mode fill) noexcept;
        static void enable_alpha_blend(blend_mode mode, blend_function_mode source, blend_function_mode destination) noexcept;
        static void enable_alpha_test(function_mode mode, float32 value) noexcept;
        static void enable_culling(culling_mode mode) noexcept;
        static void enable_depth(function_mode mode) noexcept;
        static void disable_alpha_blend(void) noexcept;
        static void disable_alpha_test(void) noexcept;
        static void disable_culling(void) noexcept;
        static void disable_depth(void) noexcept;

        // methods

        void activate(void) const noexcept;

        enable_mode get_alpha_blend(void) const noexcept
        {
            return m_alpha_blend;
        }

        blend_mode get_alpha_blend_mode(void) const noexcept
        {
            return m_alpha_blend_mode;
        }

        blend_function_mode get_alpha_blend_dst_mode(void) const noexcept
        {
            return m_alpha_blend_dst_mode;
        }

        blend_function_mode get_alpha_blend_src_mode(void) const noexcept
        {
            return m_alpha_blend_src_mode;
        }

        enable_mode get_alpha_test(void) const noexcept
        {
            return m_alpha_test;
        }

        function_mode get_alpha_test_mode(void) const noexcept
        {
            return m_alpha_test_mode;
        }

        float32 get_alpha_test_value(void) const noexcept
        {
            return m_alpha_test_value;
        }

        enable_mode get_culling(void) const noexcept
        {
            return m_culling;
        }

        culling_mode get_culling_mode(void) const noexcept
        {
            return m_culling_mode;
        }

        enable_mode get_depth(void) const noexcept
        {
            return m_depth;
        }

        function_mode get_depth_mode(void) const noexcept
        {
            return m_depth_mode;
        }

        front_face_mode get_front_face_mode(void) const noexcept
        {
            return m_front_face_mode;
        }

        polygon_face_mode get_polygon_face_mode(void) const noexcept
        {
            return m_polygon_face_mode;
        }

        polygon_fill_mode get_polygon_fill_mode(void) const noexcept
        {
            return m_polygon_fill_mode;
        }

        void
        set_alpha_blend(
            enable_mode enable,
            blend_mode mode = blend_mode::add,
            blend_function_mode source = blend_function_mode::one,
            blend_function_mode destination = blend_function_mode::one) noexcept
        {
            m_alpha_blend = enable;
            m_alpha_blend_mode = mode;
            m_alpha_blend_src_mode = source;
            m_alpha_blend_dst_mode = destination;
        }

        void
        set_alpha_test(
            enable_mode enable,
            function_mode mode = function_mode::always,
            float32 value = 1.0f) noexcept
        {
            m_alpha_test = enable;
            m_alpha_test_mode = mode;
            m_alpha_test_value = value;
        }

        void
        set_culling(
            enable_mode enable,
            culling_mode mode = culling_mode::back_face) noexcept
        {
            m_culling = enable;
            m_culling_mode = mode;
        }

        void
        set_depth(
            enable_mode enable,
            function_mode mode = function_mode::always) noexcept
        {
            m_depth = enable;
            m_depth_mode = mode;
        }

        void set_front_face(front_face_mode mode) noexcept
        {
            m_front_face_mode = mode;
        }

        void set_polygon(polygon_face_mode face, polygon_fill_mode fill) noexcept
        {
            m_polygon_face_mode = face;
            m_polygon_fill_mode = fill;
        }

    private:

        // static methods

        static uint32 get_gl_blend_function_mode(blend_function_mode mode) noexcept;
        static uint32 get_gl_blend_mode(blend_mode mode) noexcept;
        static uint32 get_gl_culling_mode(culling_mode mode) noexcept;
        static uint32 get_gl_enable_mode(enable_mode mode) noexcept;
        static uint32 get_gl_front_face_mode(front_face_mode mode) noexcept;
        static uint32 get_gl_function_mode(function_mode mode) noexcept;
        static uint32 get_gl_polygon_face_mode(polygon_face_mode mode) noexcept;
        static uint32 get_gl_polygon_fill_mode(polygon_fill_mode mode) noexcept;

    private:

        // attributes

        enable_mode m_alpha_blend;
        blend_mode m_alpha_blend_mode;
        blend_function_mode m_alpha_blend_dst_mode;
        blend_function_mode m_alpha_blend_src_mode;

        enable_mode m_alpha_test;
        function_mode m_alpha_test_mode;
        float32 m_alpha_test_value;

        enable_mode m_culling;
        culling_mode m_culling_mode;

        enable_mode m_depth;
        function_mode m_depth_mode;

        front_face_mode m_front_face_mode;

        polygon_face_mode m_polygon_face_mode;
        polygon_fill_mode m_polygon_fill_mode;
    };
}

#endif // _gg_gfx_opengl_rasterizer_h_
