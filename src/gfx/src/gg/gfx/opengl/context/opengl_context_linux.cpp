#if defined(GG_GFX_OPENGL_SUPPORT) && defined(GG_LINUX)
//==============================================================================

#include "gg/gfx/opengl/context/opengl_context_linux.h"

//==============================================================================

#include "gg/app/window/window.h"
#include "gg/gfx/gfx_log.h"
#include "gg/gfx/opengl/context/opengl_context_info.h"
#include "gg/gfx/opengl/opengl_includes.h"
#include "gg/log/logger.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

opengl_context_linux::opengl_context_linux(void) noexcept
    : m_context(nullptr)
    , m_window(None)
{
}

opengl_context_linux::~opengl_context_linux(void) noexcept
{
    GG_ASSERT(None == m_window);
    GG_ASSERT(!m_context);
}

//==============================================================================

bool8 opengl_context_linux::disable(void) noexcept
{
    return glXMakeCurrent(get_window()->get_display(), None, nullptr);
}

bool8 opengl_context_linux::enable(void) noexcept
{
    GG_RETURN_FALSE_IF(!m_context || (None == m_window));
    return glXMakeCurrent(get_window()->get_display(), m_window, m_context);
}

void opengl_context_linux::on_finalize(void) noexcept
{
    disable();

    if (m_context)
    {
        glXDestroyContext(get_window()->get_display(), m_context);
        m_context = nullptr;
    }

    if (None != m_window)
    {
        XDestroyWindow(get_window()->get_display(), m_window);
        m_window = None;
    }
}

bool8 opengl_context_linux::on_init(context_info const * info) noexcept
{
    return on_init(type::cast_static<opengl_context_info const *>(info));
}

bool8 opengl_context_linux::on_init(opengl_context_info const * info) noexcept
{
    GG_RETURN_FALSE_IF(m_context);

    GLint glx_attributes[] =
    {
        GLX_USE_GL,
        GLX_RGBA,
        GLX_RED_SIZE,
        info->m_red_size,
        GLX_GREEN_SIZE,
        info->m_green_size,
        GLX_BLUE_SIZE,
        info->m_blue_size,
        GLX_ALPHA_SIZE,
        info->m_alpha_size,
        GLX_DEPTH_SIZE,
        info->m_depth_size,
        GLX_STENCIL_SIZE,
        info->m_stencil_size,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo * visual_info =
        glXChooseVisual(
            get_window()->get_display(),
            get_window()->get_screen(),
            glx_attributes);
    GG_RETURN_FALSE_IF(!visual_info);

    m_context =
        glXCreateContext(
            get_window()->get_display(),
            visual_info,
            NULL,
            GL_TRUE);
    GG_RETURN_FALSE_IF(!m_context);

    Colormap color_map =
        XCreateColormap(
            get_window()->get_display(),
            RootWindow(
                get_window()->get_display(),
                visual_info->screen),
            visual_info->visual,
            AllocNone);

    XSetWindowAttributes window_attributes;
    window_attributes.colormap = color_map;
    window_attributes.border_pixel = 0;
    window_attributes.event_mask =
        ExposureMask |
        ButtonPressMask |
        ButtonReleaseMask |
        KeyPressMask |
        KeyReleaseMask |
        LeaveWindowMask |
        PointerMotionMask;

    m_window =
        XCreateWindow(
            get_window()->get_display(),
            RootWindow(
                get_window()->get_display(),
                visual_info->screen),
            0, 0,
            get_window()->get_width(),
            get_window()->get_height(),
            0, visual_info->depth,
            InputOutput,
            visual_info->visual,
            CWBorderPixel | CWColormap | CWEventMask,
            &window_attributes);

    GG_RETURN_FALSE_IF(
        None == m_window ||
        BadAlloc == m_window ||
        BadColor == m_window ||
        BadCursor == m_window ||
        BadMatch == m_window ||
        BadPixmap == m_window ||
        BadValue == m_window ||
        BadWindow == m_window);

    XSetStandardProperties(
        get_window()->get_display(),
        m_window,
        get_window()->get_name().c_str(),
        get_window()->get_name().c_str(),
        None,
        NULL,
        0,
        NULL);
    XMapRaised(get_window()->get_display(), m_window);

    GG_RETURN_FALSE_IF(!enable());
    GG_RETURN_FALSE_IF(GLEW_OK != glewInit());

    int32 major_version = 0;
    int32 minor_version = 0;
    string_ref opengl_version = (char8 const *) glGetString(GL_VERSION);
    // ASSERT_GL_ERROR();
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    // ASSERT_GL_ERROR();
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    // ASSERT_GL_ERROR();
    log::logger::verbose<log::gfx>(
        "Using OpenGL %s [%d.%d]",
        opengl_version.c_str(), major_version, minor_version);
    GG_RETURN_FALSE_IF(!disable());

    return true;
}

void opengl_context_linux::swap_buffer(void) noexcept
{
	glXSwapBuffers(get_window()->get_display(), m_window);
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
