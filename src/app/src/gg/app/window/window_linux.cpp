#if defined(GG_LINUX)
//==============================================================================

#include "gg/app/window/window_linux.h"

//==============================================================================

#include "gg/app/window/window_info.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

window_linux::window_linux(void) noexcept
    : m_display(nullptr)
    , m_screen(None)
{
}

window_linux::~window_linux(void) noexcept
{
    GG_ASSERT(None == m_screen);
    GG_ASSERT_NULL(m_display);
}

//==============================================================================

void window_linux::handle_messages(void) noexcept
{
    XEvent event;

    while (XPending(m_display))
    {
        XNextEvent(m_display, &event);

        switch (event.type)
        {
            case Expose:
            {
                // XGetWindowAttributes(dpy, win, &gwa);
                // glViewport(0, 0, gwa.width, gwa.height);

                break;
            }

            default:
            {
                break;
            }
        }
    }
}

void window_linux::on_finalize(void) noexcept
{
    m_screen = None;

    if (m_display)
    {
        XCloseDisplay(m_display);
        m_display = nullptr;
    }
}

bool8 window_linux::on_init(window_info const & GG_UNUSED_ARGUMENT(info)) noexcept
{
    GG_RETURN_FALSE_IF_NOT_NULL(m_display);
    GG_RETURN_FALSE_IF_FALSE(None == m_screen);

    m_display = XOpenDisplay(0);
    GG_RETURN_FALSE_IF_NULL(m_display);

    m_screen = DefaultScreen(m_display);
    return None != m_screen;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
