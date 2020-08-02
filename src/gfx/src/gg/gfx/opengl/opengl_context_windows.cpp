#if defined(GG_GFX_OPENGL_SUPPORT) && defined(GG_WINDOWS)
//==============================================================================

#include "gg/gfx/opengl/opengl_context_windows.h"

//==============================================================================

#include "gg/app/window/window.h"
#include "gg/gfx/opengl/opengl_context_info.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_context_windows::opengl_context_windows(void) noexcept
    : m_context(nullptr)
    , m_render_context(nullptr)
{
}

//==============================================================================

void opengl_context_windows::on_finalize(void) noexcept
{
    if (m_context && m_render_context)
    {
        wglMakeCurrent(nullptr, nullptr);
    }

    if (m_render_context)
    {
        wglDeleteContext(m_render_context);
        m_render_context = nullptr;
    }

    if (m_context)
    {
        ReleaseDC(get_window()->get_hwnd(), m_context);
        m_context = nullptr;
    }
}

bool8 opengl_context_windows::on_init(context_info const * info) noexcept
{
    return on_init(type::cast_static<opengl_context_info const *>(info));
}

bool8 opengl_context_windows::on_init(opengl_context_info const * info) noexcept
{
    GG_RETURN_FALSE_IF(m_context);
    GG_RETURN_FALSE_IF(m_render_context);

    m_context = GetDC(get_window()->get_hwnd());
    GG_RETURN_FALSE_IF(!m_context);

    PIXELFORMATDESCRIPTOR descriptor;
    memory::zero(&descriptor);

    descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    descriptor.nVersion = 1;
    descriptor.dwFlags =
        PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
    descriptor.iPixelType = PFD_TYPE_RGBA;
    descriptor.cColorBits =
        info->m_red_size + info->m_green_size + info->m_blue_size;
    descriptor.cDepthBits = info->m_depth_size;
    descriptor.cStencilBits = info->m_stencil_size;
    descriptor.iLayerType = PFD_MAIN_PLANE;

    int32 pixel_format = ChoosePixelFormat(m_context, &descriptor);
    GG_RETURN_FALSE_IF(0 == pixel_format);
    GG_RETURN_FALSE_IF(!SetPixelFormat(m_context, pixel_format, &descriptor));

    m_render_context = wglCreateContext(m_context);
    GG_RETURN_FALSE_IF(!m_render_context);
    GG_RETURN_FALSE_IF(!wglMakeCurrent(m_context, m_render_context));

    GG_RETURN_FALSE_IF(GLEW_OK != glewInit());
    GG_RETURN_FALSE_IF(!wglewIsSupported("WGL_ARB_create_context"));

    int32 const render_attr[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB,
        info->m_version_major,
        WGL_CONTEXT_MINOR_VERSION_ARB,
        info->m_version_minor,
        0
    };

    HGLRC render_context =
        wglCreateContextAttribsARB(m_context, nullptr, render_attr);
    GG_RETURN_FALSE_IF(!render_context);

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_render_context);

    m_render_context = render_context;
    GG_RETURN_FALSE_IF(!wglMakeCurrent(m_context, m_render_context));

    // int32 major_version = 0;
    // int32 minor_version = 0;
    // string_ref gl_version = (char8 const *) glGetString(GL_VERSION);
    // ASSERT_GL_ERROR();
    // glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    // ASSERT_GL_ERROR();
    // glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    // ASSERT_GL_ERROR();
    // gglog::logger::verbose<gglog::gfx>(
    //     "Using OpenGL %s [%d.%d]\n",
    //     gl_version.get(), major_version, minor_version);

    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
