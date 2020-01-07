#if defined(GG_LINUX)
//==============================================================================

#include "gg/app/application/application_linux.h"

//==============================================================================

#include "gg/app/window/window.h"

//==============================================================================
namespace gg
{
//==============================================================================

application_linux::application_linux(data const & data) noexcept
    : window_application(data)
{
}

//==============================================================================

window * application_linux::create_window(
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

void application_linux::destroy_window(uint32 id)
{
    window * win = get_window(id);
    if (win) { win->finalize(); }
    remove_window(id);
}

void application_linux::handle_messages(void) noexcept
{
    for_each_window(
        [](window * win)
        {
            win->handle_messages();
        });
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
