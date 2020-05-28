#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/runtime/runtime_windows.h"

//==============================================================================

#include "gg/app/window/window.h"
#include <windows.h>

//==============================================================================
namespace gg::app
{
//==============================================================================

runtime_windows::runtime_windows(data const & data) noexcept
    : runtime_base(data)
{
}

//==============================================================================

window * runtime_windows::create_window(
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

void runtime_windows::destroy_window(uint32 id)
{
    window * win = get_window(id);
    if (win) { win->finalize(); }
    remove_window(id);
}

void runtime_windows::handle_messages(void) noexcept
{
    MSG msg;

    // initialize msg

    memory::zero(&msg);

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
