#if defined(GG_LINUX)
//==============================================================================

#include "gg/app/window/window_linux.h"
#include "gg/core/macro/macro.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

window_linux::window_linux(uint32 id, string_ref const & name)
    : window_base(id, name)
    , m_display(nullptr)
    , m_screen(None)
{
}

window_linux::~window_linux(void)
{
    finalize();
}

//==============================================================================

void window_linux::finalize(void)
{
    if (m_display)
    {
        XCloseDisplay(m_display);
        m_display = nullptr;
    }
}

void window_linux::handle_messages(void)
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

    #if defined(GG_INPUT)
        // handle input
        get_input_manager()->handle_messages(event);
    #endif
    }
}

bool8 window_linux::init(uint16 width, uint16 height)
{
    GG_RETURN_FALSE_IF_NOT_NULL_ASSERT(m_display);
    GG_RETURN_FALSE_IF_FALSE_ASSERT(None == m_screen);

    set_width(width);
    set_height(height);

    // open display

    m_display = XOpenDisplay(0);
    GG_RETURN_FALSE_IF_NULL_ASSERT(m_display);

    // default screen

    m_screen = DefaultScreen(m_display);

    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
