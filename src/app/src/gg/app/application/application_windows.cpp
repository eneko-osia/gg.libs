#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/application/application_windows.h"

//==============================================================================

#include "gg/app/window/window.h"
#include <windows.h>

//==============================================================================
namespace gg
{
//==============================================================================

application_windows::application_windows(data const & data) noexcept
    : window_application(data)
{
}

//==============================================================================

window * application_windows::create_window(
    uint32 id,
    string_ref const & name,
    uint16 width,
    uint16 height)
{
    window * win = memory::new_object<window>(id, name);

    if (!win->init(width, height))
    {
        GG_ASSERT_FAILED();
        memory::delete_object(win);
        return nullptr;
    }

    add_window(win);
    return win;
}

void application_windows::destroy_window(uint32 id)
{
    window * win = get_window(id);
    if (win) { win->finalize(); }
    remove_window(id);
}

void application_windows::handle_messages(void) noexcept
{
    MSG msg;

    // initialize msg

    memory::zero(&msg, 1);

    // handle the windows messages

    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
