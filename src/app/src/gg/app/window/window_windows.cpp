//==============================================================================
#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/window/window_windows.h"

//==============================================================================

#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"
#include <windows.h>

//==============================================================================
namespace gg::app
{
//==============================================================================

static window * get_window(HWND hwnd)
{
    auto user_data = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return type::cast_reinterpret<window *>(user_data);
}

static void set_window(HWND hwnd, LPARAM lparam)
{
    auto * create_struct = type::cast_reinterpret<CREATESTRUCT *>(lparam);
    auto * win = type::cast_reinterpret<window *>(create_struct->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, type::cast_reinterpret<LONG_PTR>(win));
}

static LRESULT WINAPI wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (WM_CREATE == msg)
    {
        set_window(hwnd, lparam);
        return 0;
    }
    else if (WM_DESTROY == msg)
    {
        PostQuitMessage(0);
        return 0;
    }

    window * win = get_window(hwnd);
    return (win && win->handle_messages(msg, wparam, lparam)) ?
        0 :
        DefWindowProc(hwnd, msg, wparam, lparam);
}

//==============================================================================

window_windows::window_windows(void) noexcept
    : m_hwnd(nullptr)
    , m_wnd_class(nullptr)
{
}

window_windows::~window_windows(void)
{
    GG_ASSERT(m_hwnd.is_null());
    GG_ASSERT(m_wnd_class.is_null());
}

//==============================================================================

bool8
window_windows::handle_messages(uint32 msg, int64 wparam, int64 lparam) noexcept
{
    GG_UNUSED(lparam);

    switch(msg)
    {
        case WM_ACTIVATEAPP:
        {
            notify_observers((TRUE == wparam) ?
                &iwindow_observer::on_gain_focus :
                &iwindow_observer::on_lost_focus);
            return true;
        }

        case WM_CLOSE:
        case WM_QUIT:
        {
            notify_observers(&iwindow_observer::on_close);
            return true;
        }
    }

    return false;
}

void window_windows::on_finalize(void) noexcept
{
    if (!m_hwnd.is_null())
    {
        DestroyWindow(m_hwnd.get<HWND>());
        m_hwnd = nullptr;
    }

    unregister_class();
}

bool8 window_windows::on_init(window_info const & info) noexcept
{
    GG_RETURN_FALSE_IF(!register_class(info));
    GG_RETURN_FALSE_IF(!m_hwnd.is_null());

    DWORD window_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    RECT rect =
    {
        0, 0,
        type::cast_static<LONG>(info.m_width),
        type::cast_static<LONG>(info.m_height)
    };
    AdjustWindowRect(&rect, window_style, FALSE);

    m_hwnd =
        CreateWindow(
            info.m_name.c_str(),
            info.m_name.c_str(),
            window_style,
            0, 0,
            rect.right - rect.left, rect.bottom - rect.top,
            nullptr,
            nullptr,
            m_wnd_class.get<PWNDCLASSEX>()->hInstance,
            this);
    GG_RETURN_FALSE_IF(m_hwnd.is_null());

    HWND const hwnd = m_hwnd.get<HWND>();
    ShowWindow(hwnd, SW_SHOW);
    SetFocus(hwnd);
    UpdateWindow(hwnd);

    return true;
}

bool8 window_windows::register_class(window_info const & info) noexcept
{
    GG_RETURN_FALSE_IF(!m_wnd_class.is_null());
    GG_RETURN_FALSE_IF(info.m_hinstance.is_null());

    m_wnd_class = memory::new_object<WNDCLASSEX>();
    GG_RETURN_FALSE_IF(m_wnd_class.is_null());

    PWNDCLASSEX const wnd_class = m_wnd_class.get<PWNDCLASSEX>();
    wnd_class->cbSize = sizeof(WNDCLASSEX);
    wnd_class->style = CS_CLASSDC;
    wnd_class->lpfnWndProc = wndproc;
    wnd_class->cbClsExtra = 0;
    wnd_class->cbWndExtra = 0;
    wnd_class->hInstance = info.m_hinstance.get<HINSTANCE>();
    wnd_class->hIcon = LoadIcon(0, IDI_WINLOGO);
    wnd_class->hIconSm = wnd_class->hIcon;
    wnd_class->hCursor = LoadCursor(0, IDC_ARROW);
    wnd_class->hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wnd_class->lpszMenuName = 0;
    wnd_class->lpszClassName = info.m_name.c_str();
    return FALSE != RegisterClassEx(wnd_class);
}

bool8 window_windows::unregister_class(void) noexcept
{
    GG_RETURN_FALSE_IF(m_wnd_class.is_null());

    PWNDCLASSEX wnd_class = m_wnd_class.get<PWNDCLASSEX>();
    bool8 unregistered =
        (FALSE != UnregisterClass(get_name().c_str(), wnd_class->hInstance));

    memory::delete_object(wnd_class);
    m_wnd_class = nullptr;

    return unregistered;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
