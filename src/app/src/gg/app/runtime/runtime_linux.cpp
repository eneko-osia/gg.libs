#if defined(GG_LINUX)
//==============================================================================

#include "gg/app/runtime/runtime_linux.h"

//==============================================================================

#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

runtime_linux::runtime_linux(data const & data) noexcept
    : runtime_base(data)
{
}

//==============================================================================

id_type runtime_linux::create_window(
    string_ref const & name,
    uint16 width,
    uint16 height) noexcept
{
    window_info info;
    info.m_name = name;
    info.m_width = width;
    info.m_height = height;

    auto it = m_windows.emplace_back();
    if (!it->init(&info))
    {
        m_windows.pop_back();
        return id_type_invalid;
    }

    return id_type(m_windows.size() - 1);
}

void runtime_linux::handle_messages(void) noexcept
{
    for_each_window([] (window * win)
    {
        win->handle_messages();
    });
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
