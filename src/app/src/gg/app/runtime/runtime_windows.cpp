#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/runtime/runtime_windows.h"

//==============================================================================

#include "gg/app/data/data.h"
#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

runtime_windows::runtime_windows(data const & data) noexcept
    : runtime_base(data)
{
}

//==============================================================================

id_type runtime_windows::create_window(
    string_ref const & name,
    uint16 width,
    uint16 height) noexcept
{
    window_info info;
    info.m_name = name;
    info.m_width = width;
    info.m_height = height;
    info.m_hinstance = get_data().get_hinstance();

    auto it = m_windows.emplace_back();
    if (!it->init(&info))
    {
        m_windows.pop_back();
        return id_type_invalid;
    }

    return id_type(m_windows.size() - 1);
}

void runtime_windows::handle_messages(void) noexcept
{
    MSG msg;
    memory::zero(&msg);

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
