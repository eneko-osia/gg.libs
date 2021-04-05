//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT) && defined(GG_WINDOWS)
//==============================================================================

#include "gg/gfx/opengl/context/opengl_context_windows.h"

//==============================================================================

#include "gg/app/window/window.h"
#include "gg/gfx/gfx_log.h"
#include "gg/gfx/opengl/context/opengl_context_info.h"
#include "gg/gfx/opengl/debug/opengl_assert.h"
#include "gg/gfx/opengl/opengl_includes.h"
#include "gg/log/logger.h"

#include <windows.h>

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_context_windows::opengl_context_windows(void) noexcept
    : m_context()
    , m_hwnd()
    , m_render_context()
{
}

opengl_context_windows::~opengl_context_windows(void) noexcept
{
    GG_ASSERT(!m_render_context);
    GG_ASSERT(!m_hwnd);
    GG_ASSERT(!m_context);
}

//==============================================================================

bool8 opengl_context_windows::disable(void) noexcept
{
    return wglMakeCurrent(nullptr, nullptr);
}

bool8 opengl_context_windows::enable(void) noexcept
{
    GG_RETURN_FALSE_IF(!m_context || !m_render_context);
    return wglMakeCurrent(m_context.get<HDC>(), m_render_context.get<HGLRC>());
}

void opengl_context_windows::on_finalize(void) noexcept
{
    disable();

    if (m_render_context)
    {
        wglDeleteContext(m_render_context.get<HGLRC>());
        m_render_context = nullptr;
    }

    if (m_context)
    {
        ReleaseDC(m_hwnd.get<HWND>(), m_context.get<HDC>());
        m_context = nullptr;
    }

    m_hwnd = nullptr;
}

bool8 opengl_context_windows::on_init(opengl_context_info const & info) noexcept
{
    GG_RETURN_FALSE_IF(m_context || m_render_context);

    m_hwnd = info.m_window ? info.m_window->get_hwnd() : nullptr;
    GG_RETURN_FALSE_IF(!m_hwnd);

    m_context = GetDC(m_hwnd.get<HWND>());
    GG_RETURN_FALSE_IF(!m_context);

    PIXELFORMATDESCRIPTOR descriptor;
    memory::zero(&descriptor);

    descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    descriptor.nVersion = 1;
    descriptor.dwFlags =
        PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
    descriptor.iPixelType = PFD_TYPE_RGBA;
    descriptor.cColorBits =
        info.m_red_size + info.m_green_size + info.m_blue_size;
    descriptor.cDepthBits = info.m_depth_size;
    descriptor.cStencilBits = info.m_stencil_size;
    descriptor.iLayerType = PFD_MAIN_PLANE;

    int32 pixel_format = ChoosePixelFormat(m_context.get<HDC>(), &descriptor);
    GG_RETURN_FALSE_IF(0 == pixel_format);
    GG_RETURN_FALSE_IF(!SetPixelFormat(m_context.get<HDC>(), pixel_format, &descriptor));

    m_render_context = wglCreateContext(m_context.get<HDC>());
    GG_RETURN_FALSE_IF(!m_render_context);

    GG_RETURN_FALSE_IF(!enable());
    GG_RETURN_FALSE_IF(GLEW_OK != glewInit());
    GG_RETURN_FALSE_IF(!disable());

    wglDeleteContext(m_render_context.get<HGLRC>());

    GG_RETURN_FALSE_IF(!wglewIsSupported("WGL_ARB_create_context"));
    int32 const render_attr[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB,
        info.m_version_major,
        WGL_CONTEXT_MINOR_VERSION_ARB,
        info.m_version_minor,
        0
    };
    m_render_context =
        wglCreateContextAttribsARB(m_context.get<HDC>(), nullptr, render_attr);
    GG_RETURN_FALSE_IF(!m_render_context);

    GG_RETURN_FALSE_IF(!enable());
    int32 major = 0;
    int32 minor = 0;
    string_ref version = (char8 const *) glGetString(GL_VERSION);
    GG_ASSERT_GL_ERROR();
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    GG_ASSERT_GL_ERROR();
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    GG_ASSERT_GL_ERROR();
    log::logger::verbose<log::gfx>(
        "Using OpenGL %s [%d.%d]", version.c_str(), major, minor);
    GG_RETURN_FALSE_IF(!disable());

    return true;
}

void opengl_context_windows::swap_buffer(void) noexcept
{
    GG_ASSERT(m_context);
    SwapBuffers(m_context.get<HDC>());
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
